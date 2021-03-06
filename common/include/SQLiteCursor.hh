///////////////////////////////////////////////////////////////////////////////
//
//                          IMPORTANT NOTICE
//
// The following open source license statement does not apply to any
// entity in the Exception List published by FMSoft.
//
// For more information, please visit:
//
// https://www.fmsoft.cn/exception-list
//
//////////////////////////////////////////////////////////////////////////////
/*
** This file is a part of mg-demos package.
**
** Copyright (C) 2010 ~ 2019 FMSoft (http://www.fmsoft.cn).
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/
/*!============================================================================
 * @file SQLiteCursor.hh
 * @Synopsis
 * @author DongKai
 * @version 1.0
 *  Company: Beijing FMSoft Technology Co., Ltd.
 */

#ifndef  SQLITECURSOR_INC
#define  SQLITECURSOR_INC

#include "ContentCursor.hh"

class SQLiteCursor : public ContentCursor {
public:
    virtual ~SQLiteCursor () {close();}
    virtual void close();
    virtual void deactivate();
    virtual int getColumnCount() const;
    virtual int getColumnIndex(const std::string& name) const;
    virtual std::string getString(const std::string& columnName) const;
    virtual int getInt(const std::string& columnName, int defVal) const;
    virtual double getDouble(const std::string& columnName, double defVal) const;
    virtual size_t  getCount() const;
    virtual ContentValues::Strings getColumnNames() const;
    virtual int getPosition() const;

    virtual bool isFirst() const { return m_queryResult.begin() == m_rowIterator;}
    virtual bool isLast() const { return m_queryResult.end() == m_rowIterator; }
    virtual bool isClosed() const;
    virtual bool moveToFirst(){ m_rowIterator = m_queryResult.begin(); return true; }
    virtual bool moveToLast() { m_rowIterator = m_queryResult.end(); return true; }
    virtual bool moveToNext() {
        if (m_queryResult.end() != m_rowIterator) {
            return ++m_rowIterator != m_queryResult.end();
        }
        return false;
    }
    virtual bool moveToPosition(int pos);
    virtual bool moveToPrevious() {
        if (m_queryResult.begin() != m_rowIterator) {
            return --m_rowIterator != m_queryResult.begin();
        }
            return false;
    };

    virtual bool requery();

private:
    SQLiteCursor(SQLiteDB& db) :
        m_db(db), m_queryResult(db.lastQueryResult()) {
            refreshKeySet();
            m_rowIterator = m_queryResult.begin();
            m_queryCmd = m_db.lastSQLCmd();
        }

    // copy & assign forbidden.
    SQLiteCursor(const SQLiteCursor&);
    SQLiteCursor& operator=(const SQLiteCursor&);

    void destroyResult();
    const ContentValues* getRow(size_t num) const;
    bool refreshKeySet();

    SQLiteDB&   m_db;
    SQLiteDB::SQLCache    m_queryResult;
    ContentValues::Strings m_keySet;
    SQLiteDB::SQLCache::iterator m_rowIterator;
    std::string m_queryCmd;

    friend class SQLiteDB;
};
#endif   /* ----- #ifndef SQLITECURSOR_INC  ----- */

