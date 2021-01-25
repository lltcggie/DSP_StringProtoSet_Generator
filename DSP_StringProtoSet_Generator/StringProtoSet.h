#pragma once

#include "Serializer_Deserializer.h"


// �u���p���K�\������
// ^.+\s
// s << o.

// StringProtoSet 

namespace DSP
{
    struct PPtrObject
    {
        int32_t m_FileID;
        int64_t m_PathID;

        friend Serializer& operator<<(Serializer& s, const PPtrObject& o)
        {
            s << o.m_FileID;
            s << o.m_PathID;
            return s;
        }

        friend Deserializer& operator>>(Deserializer& d, PPtrObject& o)
        {
            d >> o.m_FileID;
            d >> o.m_PathID;
            return d;
        }
    };

    struct StringProto
    {
        std::string Name;		// ���̃e�L�X�g�̊T�v��(�ȑ̎�)
        int32_t ID;			    // ID
        std::string SID = "";	// �ڍוs��
        std::string ZHCN;		// ������(�ȑ̎�)
        std::string ENUS;		// �p��
        std::string FRFR;		// �t�����X��

        friend Serializer& operator<<(Serializer& s, const StringProto& o)
        {
            s << o.Name;
            s << o.ID;
            s << o.SID;
            s << o.ZHCN;
            s << o.ENUS;
            s << o.FRFR;
            return s;
        }

        friend Deserializer& operator>>(Deserializer& d, StringProto& o)
        {
            d >> o.Name;
            d >> o.ID;
            d >> o.SID;
            d >> o.ZHCN;
            d >> o.ENUS;
            d >> o.FRFR;
            return d;
        }
    };

    struct StringProtoSet
    {
        PPtrObject m_GameObject;
        uint8_t m_Enabled;
        PPtrObject m_Script;
        std::string m_Name;
        std::string TableName;
        std::vector<StringProto> dataArray;

        friend Serializer& operator<<(Serializer& s, const StringProtoSet& o)
        {
            s << o.m_GameObject;
            s << o.m_Enabled;
            s << o.m_Script;
            s << o.m_Name;
            s << o.TableName;
            s << o.dataArray;
            return s;
        }

        friend Deserializer& operator>>(Deserializer& d, StringProtoSet& o)
        {
            d >> o.m_GameObject;
            d >> o.m_Enabled;
            d >> o.m_Script;
            d >> o.m_Name;
            d >> o.TableName;
            d >> o.dataArray;
            return d;
        }
    };
}
