/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  �嵭����Ԥϡ�Free Software Foundation �ˤ�äƸ�ɽ����Ƥ��� 
 *  GNU General Public License �� Version 2 �˵��Ҥ���Ƥ����狼����
 *  ����(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ���
 *  ������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ�����������Ѳ�ǽ�ʥХ��ʥꥳ���ɡʥ���������֥륪��
 *      �������ȥե������饤�֥��ʤɡˤη������Ѥ�����ˤϡ�����
 *      ��ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ����
 *      �������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ�������������Բ�ǽ�ʥХ��ʥꥳ���ɤη��ޤ��ϵ������
 *      �߹�����������Ѥ�����ˤϡ����Τ����줫�ξ������������ȡ�
 *    (a) ���Ѥ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 *        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) ���Ѥη��֤��̤�������ˡ�ˤ�äơ��嵭����Ԥ���𤹤�
 *        ���ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥϡ�
 *  �ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����ޤ�ơ������ʤ��ݾڤ�Ԥ�
 *  �ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū����������
 *  ���ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: fc_bfd.cpp,v 1.6 2002/04/05 08:48:31 takayuki Exp $
 */


#include "filecontainer.h"

#include "except.h"

#include "bfd.h"
#include "libiberty.h"

#include <string>
#include <map>

using namespace std;


/*
 *  BFD��Ȥä��ե����륳��ƥʥ��饹
 */
class filecontainer_BFD : public filecontainer
{
protected:
	bfd * object;							//���֥�������
	map<string, asymbol *> symbol_table;	//�����ѥϥå����ɤ�
	asymbol ** symbol_container;

public:
	filecontainer_BFD(void);
	~filecontainer_BFD(void);

	virtual bool attach_module(const char *);
	virtual bool change_endian(void * target, unsigned int size);
	virtual bool load_contents(void * dest, unsigned long address, unsigned int size);
	virtual unsigned long get_symbol_address(const char *);
	virtual const char * get_architecture(void);

} Instance_of_filecontainer_BFD;

filecontainer_BFD::filecontainer_BFD(void)
{
	bfd_init();

	object = NULL;
	symbol_table.clear();
	symbol_container = NULL;
	instance = this;
}

filecontainer_BFD::~filecontainer_BFD(void)
{
	if(object != NULL)
		bfd_close(object);
}

/*
 *  attach_module : �оݥ⥸�塼��򥢥��å�����
 */
bool filecontainer_BFD::attach_module(const char * filename)
{
	char ** target_list;
	asymbol ** symbols;
	asymbol *  sym;
	int num_syms;
	boolean result;
	int i;

	if(object != NULL)
		bfd_close(object);
	symbol_table.clear();

		//�⥸�塼�륪���ץ� (�ɹ���)
	object = bfd_openr(filename, "default");

		//�������åȲ��
	target_list = (char **)bfd_target_list();
	result = bfd_check_format_matches(object, bfd_object, &target_list);
	if(result == 0)
		Exception("Internel error: BFD could not recognize the target file format.","�������顼: BFD�ϥե�������ɤ߽Ф��˼��Ԥ��ޤ���");

		//����ܥ�Υϥå����ɤ�����
	symbols = (asymbol **)xmalloc( bfd_get_symtab_upper_bound(object) );
	num_syms = bfd_canonicalize_symtab(object, symbols);

	for(i=0;i<num_syms;i++)
	{
		sym = *(symbols+i);
		if(sym != NULL && sym->name != NULL && *(sym->name) != '\x0')
			symbol_table[string(sym->name)] = sym;
	}

	symbol_container = symbols;
	return true;
}

bool filecontainer_BFD::change_endian(void * target, unsigned int size)
{
		//�ۥ��Ȥϥ�ȥ�Ȳ���
	enum bfd_endian host_endian = BFD_ENDIAN_LITTLE;

	char * top, * tail;

	if(object == NULL)
		return false;

	if(object->xvec->byteorder == BFD_ENDIAN_UNKNOWN)
		return false;

/*
	unsigned int __work = 0x1;
	if( *(char *)__work == 0)
		host_endian = BFD_ENDIAN_BIG;
*/

	if(object->xvec->byteorder == host_endian)
		return true;

	/*
	 *  �ᥤ��롼�� : bswap���ʤ��ǡ���ľ�˽�
	 */

	top  = (char *)target;
	tail = (char *)target+size -1;

	while(top < tail)
	{
		*top ^= *tail, *tail ^= *top, *top ^= *tail;
		top ++;
		tail --;
	}

	return true;
}


bool filecontainer_BFD::load_contents(void * dest, unsigned long address, unsigned int size)
{
	struct sec * section;

	if(object == 0)
		return false;

		//�оݥ��ɥ쥹����ͭ���륻��������õ��
	section = object->sections;
	while(section != 0)
	{
		if(address - (unsigned long)section->vma <= section->_raw_size 
			&& (section->flags & (SEC_ALLOC|SEC_HAS_CONTENTS)) == (SEC_ALLOC|SEC_HAS_CONTENTS))
		{
				//�ɤ߽Ф�
			bfd_get_section_contents(object, section, dest, address - (unsigned long)section->vma, size);
			return true;
		}
		section = section->next;
	}

		//�ɤ��ˤ�ʤ�
	Exception("Internel error: Memory read with unmapped address","�������顼; �ޥåפ���Ƥʤ����ɥ쥹��Ȥäƥ���꡼�ɤ��Ԥ��ޤ���");

	return false;
}


/*
 * get_symbol_address : ����ܥ�̾���饢�ɥ쥹�ͤ��������
 */
unsigned long filecontainer_BFD::get_symbol_address(const char * symbol)
{
	map<string, asymbol *>::iterator scope;
	string symbol_name;

	if(object == 0)
		Exception("Not initialized","���������Ƥޤ���");

		//����ܥ�̾���������� ("_"�Ȥ��ν���)
	if(object->xvec->symbol_leading_char != '\x0')
		symbol_name += object->xvec->symbol_leading_char;
	symbol_name += symbol;

	scope = symbol_table.find(symbol_name);
	if(scope == symbol_table.end())
		return 0;
		//Exception("Internal error: Unknown symbol [%s]","�������顼: �����ʥ���ܥ� [%s]").format(symbol_name.c_str());

		//Address = ����������⥪�ե��å��� + ����������VMA
	return (*scope).second->value + (*scope).second->section->vma;
}

/*
 * get_architecture : �������ƥ�����̾�μ���
 */
const char * filecontainer_BFD::get_architecture(void)
{
	if(object == NULL)
		return "Unknown";

		//�Ȥꤢ�����������å�̾����äƥ������ƥ�����̾�ˤ��Ƥ�����
		// #�ɤ����Хʡ��ˤ����ȤäƤʤ����� ���ΤȤ���
	return object->xvec->name;
}