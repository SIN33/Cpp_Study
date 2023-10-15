﻿/*=================================================================*/
/*																   */
/*		カスタムプロパティヘッダ									   */
/* 																   */
/*	vc++ 匿名共用体の機能確認				                           */
/*  整数、真偽値、文字(VCようにCStringを採用)、整数配列、真偽値配列、文字配列を扱う            */
/*=================================================================*/
#pragma once

#include <unordered_map>
#include <afxstr.h> //Cstring

enum class ENCPVKind : BYTE //カスタムプロパティの値の種別
{
	None,
	Integer,
	Boolean,
	String,
	IntegerAry,
	BooleanAry,
	StringAry
};


class CustomProperty
{
public:
	static  const CustomProperty InValidProperty;

private:
	ENCPVKind m_enKind = ENCPVKind::None;
	union
	{
		LONG m_lVal;
		bool m_bVal;
		CString m_strVal;
		std::vector<LONG> m_vLongAry;
		std::vector<bool> m_vBoolAry;
		std::vector<CString> m_vStrAry;
	};

public:
	CustomProperty() {}
	explicit CustomProperty(LONG lVal)
		: m_enKind(ENCPVKind::Integer)
		, m_lVal(lVal) {}
	explicit CustomProperty(bool bVal)
		: m_enKind(ENCPVKind::Boolean)
		, m_bVal(bVal) {}
	explicit CustomProperty(CString strVal)
		: m_enKind(ENCPVKind::String)
		, m_strVal(strVal) {}
	explicit CustomProperty(const std::vector<LONG>& vLongAry)
		: m_enKind(ENCPVKind::IntegerAry)
		, m_vLongAry(vLongAry) {}
	explicit CustomProperty(const std::vector<bool>& vBoolAry)
		: m_enKind(ENCPVKind::BooleanAry)
		, m_vBoolAry(vBoolAry) {}
	explicit CustomProperty(const std::vector<CString>& vStrAry)
		: m_enKind(ENCPVKind::StringAry)
		, m_vStrAry(vStrAry) {}
	CustomProperty(ENCPVKind enKind, LONG lVal)
		: m_enKind(enKind)
		, m_lVal(lVal) {}
	CustomProperty(ENCPVKind enKind, bool bVal)
		: m_enKind(enKind)
		, m_bVal(bVal) {}
	CustomProperty(ENCPVKind enKind, CString strVal)
		: m_enKind(enKind)
		, m_strVal(strVal) {}
	CustomProperty(ENCPVKind enKind, const std::vector<LONG>& vLongAry)
		: m_enKind(enKind)
		, m_vLongAry(vLongAry) {}
	CustomProperty(ENCPVKind enKind, const std::vector<bool>& vBoolAry)
		: m_enKind(enKind)
		, m_vBoolAry(vBoolAry) {}
	CustomProperty(ENCPVKind enKind, const std::vector<CString>& vStrAry)
		: m_enKind(enKind)
		, m_vStrAry(vStrAry) {}

	~CustomProperty()
	{
		CleanUp();
	}

	void CleanUp()
	{
		switch (m_enKind)
		{
		case ENCPVKind::None:
		case ENCPVKind::Integer:
		case ENCPVKind::Boolean:
			break;
		case ENCPVKind::String:
			m_strVal.~CString();
			break;
		case ENCPVKind::IntegerAry:
			m_vLongAry.~vector();
			break;
		case ENCPVKind::BooleanAry:
			m_vBoolAry.~vector();
			break;
		case ENCPVKind::StringAry:
			m_vStrAry.~vector();
			break;
		default:
			_ASSERT(false);
			break;
		}
	}

	//unorder_mapで使用するため、各種演算子はオーバーロードする。
	CustomProperty(const CustomProperty& cSrcCustomProperty)
		: m_enKind(cSrcCustomProperty.m_enKind)
	{
		switch (cSrcCustomProperty.m_enKind)
		{
		case ENCPVKind::None:
			break;
		case ENCPVKind::Integer:
			m_lVal = cSrcCustomProperty.m_lVal;
			break;
		case ENCPVKind::Boolean:
			m_bVal = cSrcCustomProperty.m_bVal;
			break;
		case ENCPVKind::String:
			new (&m_strVal) CString{ cSrcCustomProperty.m_strVal };
			break;
		case ENCPVKind::IntegerAry:
			new (&m_vLongAry) std::vector<LONG>{ cSrcCustomProperty.m_vLongAry };
			break;
		case ENCPVKind::BooleanAry:
			new (&m_vBoolAry) std::vector<bool>{ cSrcCustomProperty.m_vBoolAry };
			break;
		case ENCPVKind::StringAry:
			new (&m_vStrAry) std::vector<CString>{ cSrcCustomProperty.m_vStrAry };
			break;
		default:
			_ASSERT(false);
			break;
		}
	}

	CustomProperty& operator=(const CustomProperty& cSrcCustomProperty)
	{
		if (&cSrcCustomProperty != this)
		{
			switch (cSrcCustomProperty.m_enKind)
			{
			case ENCPVKind::None:
				InitKind();
				break;
			case ENCPVKind::Integer:
				Assign(cSrcCustomProperty.m_lVal);
				break;
			case ENCPVKind::Boolean:
				Assign(cSrcCustomProperty.m_bVal);
				break;
			case ENCPVKind::String:
				Assign(cSrcCustomProperty.m_strVal);
				break;
			case ENCPVKind::IntegerAry:
				Assign(cSrcCustomProperty.m_vLongAry);
				break;
			case ENCPVKind::BooleanAry:
				Assign(cSrcCustomProperty.m_vBoolAry);
				break;
			case ENCPVKind::StringAry:
				Assign(cSrcCustomProperty.m_vStrAry);
				break;
			default:
				_ASSERT(false);
				break;
			}
		}
		return *this;
	}

	CustomProperty& CustomProperty::operator=(LONG lVal)
	{
		Assign(lVal);
		return *this;
	}

	CustomProperty& CustomProperty::operator=(bool bVal)
	{
		Assign(bVal);
		return *this;
	}

	CustomProperty& CustomProperty::operator=(CString strVal)
	{
		Assign(strVal);
		return *this;
	}

	CustomProperty& CustomProperty::operator=(const std::vector<LONG>& vLongAry)
	{
		Assign(vLongAry);
		return *this;
	}

	CustomProperty& CustomProperty::operator=(const std::vector<bool>& vBoolAry)
	{
		Assign(vBoolAry);
		return *this;
	}

	CustomProperty& CustomProperty::operator=(const std::vector<CString>& vStrAry)
	{
		Assign(vStrAry);
		return *this;
	}

	CustomProperty(CustomProperty&& cSrcCustomProperty) noexcept
		: m_enKind(cSrcCustomProperty.m_enKind)
	{
		switch (cSrcCustomProperty.m_enKind)
		{
		case ENCPVKind::None:
			break;
		case ENCPVKind::Integer:
			m_lVal = cSrcCustomProperty.m_lVal;
			break;
		case ENCPVKind::Boolean:
			m_bVal = cSrcCustomProperty.m_bVal;
			break;
		case ENCPVKind::String:
			new (&m_strVal) CString{ std::move(cSrcCustomProperty.m_strVal) };
			break;
		case ENCPVKind::IntegerAry:
			new (&m_vLongAry) std::vector<LONG>{std::move(cSrcCustomProperty.m_vLongAry) };
			break;
		case ENCPVKind::BooleanAry:
			new (&m_vBoolAry) std::vector<bool>{std::move(cSrcCustomProperty.m_vBoolAry) };
			break;
		case ENCPVKind::StringAry:
			new (&m_vStrAry) std::vector<CString>{ std::move(cSrcCustomProperty.m_vStrAry) };
			break;
		default:
			_ASSERT(false);
			break;
		}
		cSrcCustomProperty.CleanUp();
		cSrcCustomProperty.m_enKind = ENCPVKind::None;
	}


	CustomProperty& operator=(CustomProperty&& cSrcCustomProperty) noexcept
	{
		if (this != &cSrcCustomProperty)
		{
			switch (cSrcCustomProperty.m_enKind)
			{
			case ENCPVKind::None:
				InitKind();
				break;
			case ENCPVKind::Integer:
				Assign(cSrcCustomProperty.m_lVal);
				break;
			case ENCPVKind::Boolean:
				Assign(cSrcCustomProperty.m_bVal);
				break;
			case ENCPVKind::String:
				Assign(cSrcCustomProperty.m_strVal);
				break;
			case ENCPVKind::IntegerAry:
				Move(std::move(cSrcCustomProperty.m_vLongAry));
				break;
			case ENCPVKind::BooleanAry:
				Move(std::move(cSrcCustomProperty.m_vBoolAry));
				break;
			case ENCPVKind::StringAry:
				Move(std::move(cSrcCustomProperty.m_vStrAry));
				break;
			default:
				_ASSERT(false);
				break;
			}
			cSrcCustomProperty.m_enKind = ENCPVKind::None;
		}
		return *this;
	}


	bool HasKind(ENCPVKind enKind) const
	{
		return  (enKind == m_enKind);
	}


	//なにも設定されていないプロパティかどうか判定する。
	bool IsNil() const
	{
		return (m_enKind == ENCPVKind::None) || (this == &CustomProperty::InValidProperty);
	}

	ENCPVKind GetKind() const
	{
		return m_enKind;
	}


	LONG GetInt() const
	{
		ASSERT(m_enKind == ENCPVKind::Integer);
		return m_lVal;
	}

	bool GetBool() const
	{
		ASSERT(m_enKind == ENCPVKind::Boolean);
		return m_bVal;
	}

	const CString& GetString() const
	{
		ASSERT(m_enKind == ENCPVKind::String);
		return m_strVal;
	}

	const std::vector<LONG>& GetIntAry() const
	{
		ASSERT(m_enKind == ENCPVKind::IntegerAry);
		return m_vLongAry;
	}

	const std::vector<bool>& GetBoolAry() const
	{
		ASSERT(m_enKind == ENCPVKind::BooleanAry);
		return m_vBoolAry;
	}

	const std::vector<CString>& GetStringAry() const
	{
		ASSERT(m_enKind == ENCPVKind::StringAry);
		return m_vStrAry;
	}

	bool IsEqual(const CustomProperty& cCustomProperty) const
	{
		if (cCustomProperty.HasKind(ENCPVKind::None))
		{
			//ENCPVKind::Noneは無効値のため常にfalseを返す。
			return false;
		}
		if (m_enKind != cCustomProperty.GetKind())
		{
			return false;
		}
		switch (m_enKind)
		{
			case ENCPVKind::Integer:
				return m_lVal == cCustomProperty.GetInt();
			case ENCPVKind::Boolean:
				return m_bVal == cCustomProperty.GetBool();
			case ENCPVKind::String:
				return m_strVal == cCustomProperty.GetString();
			case ENCPVKind::IntegerAry:
				return m_vLongAry == cCustomProperty.GetIntAry();
			case ENCPVKind::BooleanAry:
				return m_vBoolAry == cCustomProperty.GetBoolAry();
			case ENCPVKind::StringAry:
				return m_vStrAry == cCustomProperty.GetStringAry();
			default:
				ASSERT(FALSE);
		}
		return false;
	}

	//値を文字列に変換する
	CString ValToStr() const
	{
		switch (GetKind())
		{
		case ENCPVKind::None:
			return CString(); //空文字
		case ENCPVKind::Integer:
		{
			CString strWk;
			strWk.Format(_T("%d"), GetInt());
			return strWk;
		}
		case ENCPVKind::Boolean:
		{
			CString strWk = GetBool() ? _T("True") : _T("False");
			return strWk;
		}
		case ENCPVKind::String:
			return GetString();
		case ENCPVKind::IntegerAry:
		{
			CString strWk;
			for (auto lVal : GetIntAry())
			{
				strWk.AppendFormat(_T("%d,"), lVal);
			}
			strWk.Delete(strWk.GetLength() - 1);
			return strWk;
		}
		case ENCPVKind::BooleanAry:
		{
			CString strWk;
			for (auto bVal : GetBoolAry())
			{
				strWk += bVal ? _T("True") : _T("False");
				strWk += _T(",");
			}
			strWk.Delete(strWk.GetLength() - 1);
			return strWk;
		}
		case ENCPVKind::StringAry:
		{
			CString strWk;
			for (auto strVal : GetStringAry())
			{
				strWk += strVal;
				strWk += _T(",");
			}
			strWk.Delete(strWk.GetLength() - 1);
			return strWk;
		}
		default:
			_ASSERT(false);
			return CString(); //空文字
		}
	}

private:
	void InitKind()
	{
		CleanUp();
		m_enKind = ENCPVKind::None;
	}

	void Assign(LONG lVal)
	{
		if (m_enKind != ENCPVKind::Integer)
		{
			CleanUp();
			m_enKind = ENCPVKind::Integer;
		}
		m_lVal = lVal;
	}

	void Assign(bool bVal)
	{
		if (m_enKind != ENCPVKind::Boolean)
		{
			CleanUp();
			m_enKind = ENCPVKind::Boolean;
		}
		m_bVal = bVal;
	}

	void Assign(CString strVal)
	{
		if (m_enKind != ENCPVKind::String)
		{
			CleanUp();
			new (&m_strVal) CString{ strVal };
			m_enKind = ENCPVKind::String;
		}
		else
		{
			m_strVal = strVal;
		}
	}

	void Assign(const std::vector<LONG>& vLongAry)
	{
		if (m_enKind != ENCPVKind::IntegerAry)
		{
			CleanUp();
			new (&m_vLongAry) std::vector<LONG>{ vLongAry };
			m_enKind = ENCPVKind::IntegerAry;
		}
		else
		{
			m_vLongAry = vLongAry;
		}
	}

	void Assign(const std::vector<bool>& vBoolAry)
	{
		if (m_enKind != ENCPVKind::BooleanAry)
		{
			CleanUp();
			new (&m_vBoolAry) std::vector<bool>{ vBoolAry };
			m_enKind = ENCPVKind::BooleanAry;
		}
		else
		{
			m_vBoolAry = vBoolAry;
		}
	}

	void Assign(const std::vector<CString>& vStrAry)
	{
		if (m_enKind != ENCPVKind::StringAry)
		{
			CleanUp();
			new (&m_vStrAry) std::vector<CString>{ vStrAry };
			m_enKind = ENCPVKind::StringAry;
		}
		else
		{
			m_vStrAry = vStrAry;
		}
	}

	void Move(std::vector<LONG>&& vLongAry)
	{
		if (m_enKind != ENCPVKind::IntegerAry)
		{
			CleanUp();
			new (&m_vLongAry) std::vector<LONG>{std::move(vLongAry)};
			m_enKind = ENCPVKind::IntegerAry;
		}
		else
		{
			m_vLongAry = std::move(vLongAry);
		}
	}


	void Move(std::vector<bool>&& vBoolAry)
	{
		if (m_enKind != ENCPVKind::BooleanAry)
		{
			CleanUp();
			new (&m_vBoolAry) std::vector<bool>{std::move(vBoolAry) };
			m_enKind = ENCPVKind::BooleanAry;
		}
		else
		{
			m_vBoolAry = std::move(vBoolAry);
		}
	}

	void Move(std::vector<CString>&& vStrAry)
	{
		if (m_enKind != ENCPVKind::StringAry)
		{
			CleanUp();
			new (&m_vStrAry) std::vector<CString>{ std::move(vStrAry) };
			m_enKind = ENCPVKind::StringAry;
		}
		else
		{
			m_vStrAry = std::move(vStrAry);
		}
	}
};

__declspec(selectany) const CustomProperty CustomProperty::InValidProperty;

class CAcCustomProperties
{
	using StrHash = _HashCString<CString>;
	using _CAcCustomProperties = std::unordered_map<CString, CustomProperty, StrHash>;

public:
	static const CAcCustomProperties InValidProperties;

private:
	_CAcCustomProperties m_cCustomProperties;

public:
	CAcCustomProperties() = default;

	template<typename T, typename KEYTYPE>
	T GetValue(KEYTYPE strKey) const
	{
		const auto& cProperty = GetCustomProperty(strKey);
		if (cProperty.IsNil())
		{
			T{};
		}
		return _GetValue<T>(cProperty);
	}

	size_t Size() const
	{
		return m_cCustomProperties.size();
	}

	//コレクション同士の比較
	//自身の持つプロパティと同一の物が別のカスタムプロパティコレクションの内部に存在するかどうか判定する。
	//@param const CAcCutomoProperties& cOtherCustomProperties : 別のカスタムプロパティコレクション
	bool CheckOwnPropertyInOtherProperties(const CAcCustomProperties& cOtherCustomProperties) const
	{
		for (auto it = m_cCustomProperties.begin(); it != m_cCustomProperties.end(); ++it)
		{
			//比較対象のプロパティの中に設定キーが存在するか調べる。 
			CString strTargetKeyName = it->first;
			if (!cOtherCustomProperties.ExistKeyName(strTargetKeyName))
			{
				continue;
			}
			//存在した場合、値が致しているか調べる
			const auto& cTaregetProperty = it->second;
			const auto& cOtherProperty = cOtherCustomProperties.GetCustomProperty(strTargetKeyName);
			if (cTaregetProperty.IsEqual(cOtherProperty))
			{
				//同一のプロパティが存在していた場合
				return true;
			}
		}
		return false;
	}

	bool IsEmpty() const
	{
		return m_cCustomProperties.empty();
	}

	//取得関数
	ENCPVKind GetKind(CString strKeyName) const
	{
		auto it = m_cCustomProperties.find(strKeyName);
		if (it != m_cCustomProperties.end())
		{
			return it->second.GetKind();
		}
		//キーが存在しない場合
		return ENCPVKind::None;
	}

	const CustomProperty& GetCustomProperty(CString strKeyName) const
	{
		auto it = m_cCustomProperties.find(strKeyName);
		if (it != m_cCustomProperties.end())
		{
			return it->second;
		}
		//キーが存在しない場合
		return CustomProperty::InValidProperty;
	}

	const CustomProperty& GetCustomProperty(int nIndex) const
	{
		int nCount = 0;
		for (auto it = m_cCustomProperties.begin(); it != m_cCustomProperties.end(); ++it)
		{
			if (nIndex == nCount)
			{
				return it->second;
			}
			++nCount;
		}
		return CustomProperty::InValidProperty;
	}

	const CString& GetKeyNameAtNumber(int nIndex) const
	{
		int nCount = 0;
		for (auto it = m_cCustomProperties.begin(); it != m_cCustomProperties.end(); ++it)
		{
			if (nIndex == nCount)
			{
				return it->first;
			}
			++nCount;
		}
		static const CString InValidKeyName = {};
		return InValidKeyName;
	}

	//ユーティリティ
	CString GetPropertyValWithString(int nIndex) const
	{
		return GetCustomProperty(nIndex).ValToStr();
	}

	//操作
	/**
	 * @brief 指定したキー名称の値をを更新する
	 * @param strKeyName  更新対象のキー
	 * @param cCustomProperty 更新後の値
	 * @return true:成功　false:失敗
	 */
	template<typename T>
	bool ReplaceVaule(CString strKeyName, T Value)
	{
		auto it = m_cCustomProperties.find(strKeyName);
		if (it == m_cCustomProperties.end())
		{
			//更新対象のキーが存在しない場合
			return false;
		}
		it->second = Value;
		return true;
	}

	template<typename T>
	bool SetProperty(CString strKeyName, T Value)
	{
		if (ExistKeyName(strKeyName))
		{
			return false;
		}
		CustomProperty cNewProperty{ Value };
		m_cCustomProperties.emplace(strKeyName, std::move(cNewProperty));
		return true;
	}

	void Remove(CString strKeyName)
	{
		m_cCustomProperties.erase(strKeyName);
	}

	void Clear()
	{
		m_cCustomProperties.clear();
	}

	//判定
	bool ExistKeyName(CString strKeyName) const
	{
		auto it = m_cCustomProperties.find(strKeyName);
		return (it != m_cCustomProperties.end());
	}

private:
	//spetilize
	template<typename T>
	T GetDefaultValue(CString strKeyName, CustomProperty& cCustomProperty) const //GetValueの補助関数(c++17以降はconstepxr ifでもう少し簡潔に書ける)
	{
		cCustomProperty = GetCustomProperty(strKeyName);
		if (cProperty.IsNil())
		{
			return T{};
		}
	}

	template<typename T>
	T _GetValue(const CustomProperty& cCustomProperty) const 
	{
		return;
	}
};

template <>
inline LONG CAcCustomProperties::_GetValue(const CustomProperty& cProperty) const
{
	return cProperty.GetInt();
}

template <>
inline bool CAcCustomProperties::_GetValue(const CustomProperty& cProperty) const
{
	return cProperty.GetBool();
}

template <>
inline CString CAcCustomProperties::_GetValue(const CustomProperty& cProperty) const
{
	return cProperty.GetString();
}

template <>
inline std::vector<LONG> CAcCustomProperties::_GetValue(const CustomProperty& cProperty) const
{
	return cProperty.GetIntAry();
}

template <>
inline std::vector<bool> CAcCustomProperties::_GetValue(const CustomProperty& cProperty) const
{
	return cProperty.GetBoolAry();
}

template <>
inline std::vector<CString> CAcCustomProperties::_GetValue(const CustomProperty& cProperty) const
{
	return cProperty.GetStringAry();
}


__declspec(selectany) const CAcCustomProperties CAcCustomProperties::InValidProperties;

namespace CustomPropertyHellper
{
	//Hellper
	//配列に対して、サイズと値の読み込みを行う。
	template<typename T>
	inline void LoadAry(CFile& fFile, T& vAry)
	{
		typedef typename T::value_type ElmType; //配列内の要素の型
		WORD wArySize = 0;
		fFile >> wArySize; //ファイルから配列のサイズを読み込む
		ElmType	elm = {};
		for (int i = 0; i < wArySize; ++i)
		{
			fFile >> elm;
			vAry.emplace_back(elm);
		}
	}
	//配列の、サイズと値を保存する。
	template<typename T>
	inline void SaveAry(CFile& fFile, T vAry)
	{
		auto nArySize = vAry.size();
		fFile << ClbCastWord(nArySize); //配列のサイズ保存
		//配列の各要素を保存する。
		for (const auto& it : vAry)
		{
			fFile << it;
		}
	}
};