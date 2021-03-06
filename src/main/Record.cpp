#include "Record.hpp"
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <cerrno>

template<class KeyType>
KeyType Record<KeyType>::getKey() const
{
    return mKey;
}

WordRecord::WordRecord(const string& str)
{
    vector<string> inputs = split(str, '\t');
    if (inputs.size() != 6)
    {
        throw * (new runtime_error("Broken record!"));
    }
    mKey = inputs[0];
    mExample = inputs[1];
    mExplanation = inputs[2];
    switch (inputs[3][0] - '0')
    {
    case 0:
        mGroup = Group::UNSEEN;
        break;
    case 1:
        mGroup = Group::LEARN;
        break;
    case 2:
        mGroup = Group::YOUNG;
        break;
    case 3:
        mGroup = Group::MATURE;
        break;
    case 4:
        mGroup = Group::RELEARN;
        break;
    case 5:
        mGroup = Group::SUSPENDED;
        break;
    default:
        throw * (new runtime_error("Broken record!"));
    }

    char* e;
    vector<string> ans = split(inputs[4], ';');
    for (size_t i = 0; i < ans.size(); i++)
    {
        errno = 0;
        mAnswers.push_back(strtol(ans[i].c_str(), &e, 10));
        if (*e != '\0' || errno != 0)
        {
            throw * (new runtime_error("Broken record!"));
        }
    }

    vector<string> alg = split(inputs[5], ';');
    for (size_t i = 0; i < alg.size(); i++)
    {
        errno = 0;
        mAlgorithmOutput.push_back(strtod(alg[i].c_str(), &e));
        if (*e != '\0' || errno != 0)
        {
            throw * (new runtime_error("Broken record!"));
        }
    }
}

string WordRecord::toString() const
{
    stringstream ss;
    ss << escape(mKey, '\t', ' ') << '\t' << escape(mExample, '\t', ' ') << '\t'
       << escape(mExplanation, '\t', ' ') << '\t' << char(int(mGroup) + '0') << '\t';
    for (size_t i = 0; i < mAnswers.size(); ++i)
    {
        if (i > 0)
        {
            ss << ';';
        }
        ss << char(mAnswers[i] + '0');
    }
    ss << '\t';
    for (size_t i = 0; i < mAlgorithmOutput.size(); ++i)
    {
        if (i > 0)
        {
            ss << ';';
        }
        ss << mAlgorithmOutput[i];
    }
    return ss.str();
}

string WordRecord::getExample() const
{
    return mExample;
}

string WordRecord::getExplanation() const
{
    return mExplanation;
}

Group WordRecord::getGroup() const
{
    return mGroup;
}

const vector<int>& WordRecord::getAnswers() const
{
    return mAnswers;
}

const vector<double>& WordRecord::getAlgorithmOutput() const
{
    return mAlgorithmOutput;
}

void WordRecord::setExample(string exp)
{
    mExample = exp;
}

void WordRecord::setGroup(Group group)
{
    mGroup = group;
}

void WordRecord::setAlgorithmOutput(vector<double> al)
{
    mAlgorithmOutput = al;
}

void WordRecord::addAnswer(int m)
{
    mAnswers.push_back(m);
}

HistoryRecord::HistoryRecord(string str, bool newRecord)
{
    if (newRecord)
    {
        mKey = str;
        mTimestamp = getCurrentTimeStamp();
    }
    else
    {
        vector<string> inputs = split(str, '\t');
        if (inputs.size() != 2)
        {
            throw * (new runtime_error("Broken record!"));
        }
        mKey = inputs[0];
        char* e;
        errno = 0;
        mTimestamp = strtoll(inputs[1].c_str(), &e, 10);
        if (*e != '\0' || errno != 0)
        {
            throw * (new runtime_error("Broken record!"));
        }
    }
}

string HistoryRecord::toString() const
{
    stringstream ss;
    ss << mKey << "\t" << mTimestamp;
    return ss.str();
}

long long HistoryRecord::getTimeStamp() const
{
    return mTimestamp;
}

void HistoryRecord::setTimeStamp(long long timestamp)
{
    mTimestamp = timestamp;
}

template class Record<string>;
