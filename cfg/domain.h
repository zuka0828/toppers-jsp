/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  上記著作権者は，Free Software Foundation によって公表されている 
 *  GNU General Public License の Version 2 に記述されている条件か，以
 *  下の条件のいずれかを満たす場合に限り，本ソフトウェア（本ソフトウェ
 *  アを改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを再利用可能なバイナリコード（リロケータブルオブ
 *      ジェクトファイルやライブラリなど）の形で利用する場合には，利用
 *      に伴うドキュメント（利用者マニュアルなど）に，上記の著作権表示，
 *      この利用条件および下記の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを再利用不可能なバイナリコードの形または機器に組
 *      み込んだ形で利用する場合には，次のいずれかの条件を満たすこと．
 *    (a) 利用に伴うドキュメント（利用者マニュアルなど）に，上記の著作
 *        権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 利用の形態を，別に定める方法によって，上記著作権者に報告する
 *        こと．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者を免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者は，
 *  本ソフトウェアに関して，その適用可能性も含めて，いかなる保証も行わ
 *  ない．また，本ソフトウェアの利用により直接的または間接的に生じたい
 *  かなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: domain.h,v 1.3 2001/11/12 14:59:27 takayuki Exp $
 */


#ifndef __DOMAIN_H
#define __DOMAIN_H

//ITRON保護機構 プロテクションドメイン対応用クラス
//  親がSharedで子がSystemって考えて作ってます

/*
 * このファイルは過渡的なものであり，次のバージョンでは削除される可能性がある．
 */

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include "parser.h"
#include <list>
#include <map>
#include <string>

class ProtectionDomain : public ParserComponent
{
public:
	enum tagDomainType
	{
		UNKNOWN,
		USER,
		SYSTEM,
		SHARED
	};

protected:
	static std::map<std::string, ProtectionDomain *> Domain;
	
	enum tagDomainType Type;
	std::string Name;
	ProtectionDomain * ParentDomain;
	std::list<ProtectionDomain *> ChildDomain;

	virtual ProtectionDomain * CreateNewDomain(Manager *) =0;
public:
	ProtectionDomain(void);
	virtual ~ProtectionDomain(void);

	operator const enum tagDomainType (void) const;

	ProtectionDomain * GetParentDomain(void);
	ProtectionDomain * GetChildDomain(ProtectionDomain * = NULL);
	ProtectionDomain * FindDomain(std::string &);

	enum tagDomainType  GetType(void) { return Type; };
	const std::string & GetName(void) { return Name; };

	virtual void Parse(class Manager *, class Parser *);
};

inline ProtectionDomain::operator const enum ProtectionDomain::tagDomainType (void) const
{	return Type;	}

inline ProtectionDomain * ProtectionDomain::GetParentDomain(void)
{	return ParentDomain;	}

inline ProtectionDomain * ProtectionDomain::FindDomain(std::string & src)
{
	std::map<std::string, ProtectionDomain *>::iterator scope;
	
	if((scope = Domain.find(src)) == Domain.end())
		return NULL;
	return (*scope).second;
}

#endif