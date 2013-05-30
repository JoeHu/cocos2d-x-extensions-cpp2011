/*
 * Copyright (c) 2013 Sergey Shambir
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef CCBINARYDATA_H
#define CCBINARYDATA_H

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

/**
 * @brief Keeps data and some meta information to reduce memory reallocations
 * when possible. Use \a createAsCopy() if source can be destroyed before
 * using CCBinaryData, use \a canonicalData() to ensure that you can use
 * BinaryData instance as normal string and pass without limitations.
 */
class CCBinaryData : public CCObject
{
public:
    /// @name createAsCopy
    /// @brief This methods family allocates memory for copy of passed data.
    /// @{
    static CCBinaryData *createAsCopy(const std::string &data);
    static CCBinaryData *createAsCopy(const std::vector<char> &data);
    static CCBinaryData *createAsCopy(const char *data, int size);
    static CCBinaryData *createAsCopy(const char *nullTerminatedData);
    /// @}

    /// @name createAsReference
    /// @brief This methods family uses existing buffer, so app will crash
    /// if you release referenced memory while using CCBinaryData instance.
    /// @{
    static CCBinaryData *createAsReference(const std::string &data);
    static CCBinaryData *createAsReference(const std::vector<char> &data);
    static CCBinaryData *createAsReference(const char *data, int size);
    static CCBinaryData *createAsReference(const char *nullTerminatedData);
    /// @}

    /// @return Null-terminated, allocated data - either \a source or its copy.
    static CCBinaryData *canonicalData(CCBinaryData *source);

    /// @name Properties
    /// @{
    const char *data() const;
    int size() const;
    bool isNullTerminated() const;
    /// @}

    /// @name Allocated utils
    /// @brief Operations on allocated null-terminated data.
    /// @{
    void appendChunk(const char *data, int size);
    /// @}

    ~CCBinaryData();

protected:
    // TODO: copyWithZone

private:
    CCBinaryData();

    const char *m_data;
    int m_size;
    bool m_isNullTerminated;
    /// Allocated must be also null-terminated.
    bool m_isAllocated;
};

NS_CC_EXT_END

#endif // CCBINARYDATA_H
