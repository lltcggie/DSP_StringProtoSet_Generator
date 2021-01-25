#pragma once

#include <string>
#include <vector>
#include <stdint.h>


inline uint32_t padding(uint32_t size, uint32_t paddingSize)
{
    return size + (size % paddingSize ? paddingSize - (size % paddingSize) : 0);
}

class Serializer
{
public:
    Serializer()
    {}

    void clear()
    {
        mData.clear();
    }

    const std::vector<uint8_t>& getData() const
    {
        return mData;
    }

    friend Serializer& operator<<(Serializer& s, int8_t o)
    {
        const auto size = sizeof(int8_t);
        const auto dataSize = padding(sizeof(int8_t), 4u);
        const auto pos = s.mData.size();
        s.mData.resize(pos + dataSize, 0);
        memcpy(&s.mData[pos], &o, size);

        return s;
    }

    friend Serializer& operator<<(Serializer& s, uint8_t o)
    {
        const auto size = sizeof(uint8_t);
        const auto dataSize = padding(sizeof(uint8_t), 4u);
        const auto pos = s.mData.size();
        s.mData.resize(pos + dataSize, 0);
        memcpy(&s.mData[pos], &o, size);

        return s;
    }

    friend Serializer& operator<<(Serializer& s, int32_t o)
    {
        const auto size = sizeof(int32_t);
        const auto dataSize = padding(sizeof(int32_t), 4u);
        const auto pos = s.mData.size();
        s.mData.resize(pos + dataSize, 0);
        memcpy(&s.mData[pos], &o, size);

        return s;
    }

    friend Serializer& operator<<(Serializer& s, uint32_t o)
    {
        const auto size = sizeof(uint32_t);
        const auto dataSize = padding(sizeof(uint32_t), 4u);
        const auto pos = s.mData.size();
        s.mData.resize(pos + dataSize, 0);
        memcpy(&s.mData[pos], &o, size);

        return s;
    }

    friend Serializer& operator<<(Serializer& s, int64_t o)
    {
        const auto size = sizeof(int64_t);
        const auto dataSize = padding(sizeof(int64_t), 4u);
        const auto pos = s.mData.size();
        s.mData.resize(pos + dataSize, 0);
        memcpy(&s.mData[pos], &o, size);

        return s;
    }

    friend Serializer& operator<<(Serializer& s, uint64_t o)
    {
        const auto size = sizeof(uint64_t);
        const auto dataSize = padding(sizeof(uint64_t), 4u);
        const auto pos = s.mData.size();
        s.mData.resize(pos + dataSize, 0);
        memcpy(&s.mData[pos], &o, size);

        return s;
    }

    friend Serializer& operator<<(Serializer& s, float o)
    {
        const auto size = sizeof(float);
        const auto dataSize = padding(sizeof(float), 4u);
        const auto pos = s.mData.size();
        s.mData.resize(pos + dataSize, 0);
        memcpy(&s.mData[pos], &o, size);

        return s;
    }

    friend Serializer& operator<<(Serializer& s, const std::string& o)
    {
        const uint32_t size = static_cast<uint32_t>(o.size());
        s << size;

        if (size > 0) {
            const auto dataSize = padding(size, 4u);
            const auto pos = s.mData.size();
            s.mData.resize(pos + dataSize, 0);
            memcpy(&s.mData[pos], o.c_str(), size);
        }

        return s;
    }

    template<class T>
    friend Serializer& operator<<(Serializer& s, const std::vector<T>& o)
    {
        const uint32_t size = static_cast<uint32_t>(o.size());
        s << size;

        for (size_t i = 0; i < o.size(); i++) {
            s << o[i];
        }

        return s;
    }

private:
    std::vector<uint8_t> mData;
};

class Deserializer
{
public:
    Deserializer() : mPos(0)
    {}

    void clear()
    {
        mData.clear();
        mPos = 0;
    }

    void setData(std::vector<uint8_t> data)
    {
        mData = std::move(data);
    }

    friend Deserializer& operator>>(Deserializer& d, int8_t& o)
    {
        const auto size = sizeof(int8_t);
        const auto dataSize = padding(sizeof(int8_t), 4u);
        memcpy(&o, &d.mData[d.mPos], size);
        d.mPos += size + (dataSize > size ? dataSize - size : 0);

        return d;
    }

    friend Deserializer& operator>>(Deserializer& d, uint8_t& o)
    {
        const auto size = sizeof(uint8_t);
        const auto dataSize = padding(sizeof(uint8_t), 4u);
        memcpy(&o, &d.mData[d.mPos], size);
        d.mPos += size + (dataSize > size ? dataSize - size : 0);

        return d;
    }

    friend Deserializer& operator>>(Deserializer& d, int32_t& o)
    {
        const auto size = sizeof(int32_t);
        const auto dataSize = padding(sizeof(int32_t), 4u);
        memcpy(&o, &d.mData[d.mPos], size);
        d.mPos += size + (dataSize > size ? dataSize - size : 0);

        return d;
    }

    friend Deserializer& operator>>(Deserializer& d, uint32_t& o)
    {
        const auto size = sizeof(uint32_t);
        const auto dataSize = padding(sizeof(uint32_t), 4u);
        memcpy(&o, &d.mData[d.mPos], size);
        d.mPos += size + (dataSize > size ? dataSize - size : 0);

        return d;
    }

    friend Deserializer& operator>>(Deserializer& d, int64_t& o)
    {
        const auto size = sizeof(int64_t);
        const auto dataSize = padding(sizeof(int64_t), 4u);
        memcpy(&o, &d.mData[d.mPos], size);
        d.mPos += size + (dataSize > size ? dataSize - size : 0);

        return d;
    }

    friend Deserializer& operator>>(Deserializer& d, uint64_t& o)
    {
        const auto size = sizeof(uint64_t);
        const auto dataSize = padding(sizeof(uint64_t), 4u);
        memcpy(&o, &d.mData[d.mPos], size);
        d.mPos += size + (dataSize > size ? dataSize - size : 0);

        return d;
    }

    friend Deserializer& operator>>(Deserializer& d, float& o)
    {
        const auto size = sizeof(float);
        const auto dataSize = padding(sizeof(float), 4u);
        memcpy(&o, &d.mData[d.mPos], size);
        d.mPos += size + (dataSize > size ? dataSize - size : 0);

        return d;
    }

    friend Deserializer& operator>>(Deserializer& d, std::string& o)
    {
        uint32_t size;
        d >> size;

        if (size > 0) {
            const auto dataSize = padding(size, 4u);
            std::vector<char> temp(size);
            memcpy(temp.data(), &d.mData[d.mPos], size);
            o.assign(temp.data(), size);
            d.mPos += size + (dataSize > size ? dataSize - size : 0);
        }

        return d;
    }

    template<class T>
    friend Deserializer& operator>>(Deserializer& d, std::vector<T>& o)
    {
        uint32_t size;
        d >> size;

        o.resize(size);
        for (size_t i = 0; i < o.size(); i++) {
            d >> o[i];
        }

        return d;
    }

private:
    std::vector<uint8_t> mData;
    size_t mPos;
};
