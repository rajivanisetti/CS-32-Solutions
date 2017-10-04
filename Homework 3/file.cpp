//
//  main.cpp
//  Homework 3
//
//  Created by Rajiv Anisetti on 2/9/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;


class File
{
public:
    File(string name)
    {
        m_name = name;
    }
    string name() const
    {
        return m_name;
    }
    virtual void open() const = 0;
    virtual void redisplay() const = 0;
    virtual ~File()
    {}
    
private:
    string m_name;
};

class TextMsg: public File
{
public:
    TextMsg(string name)
    :File(name) {}
    
    virtual void open() const
    {
        cout << "open text message";
    }
    virtual void redisplay() const
    {
        cout << "refresh the screen";
    }
    virtual ~TextMsg()
    {
        cout << "Destroying " << name() << ", a text message" << endl;
    }
};

class Video: public File
{
public:
    Video(string name, int seconds)
    :File(name), m_seconds(seconds) {}
    
    virtual void open() const
    {
        cout << "play " << m_seconds << " second video";
    }
    virtual void redisplay() const
    {
        cout << "replay video";
    }
    virtual ~Video()
    {
        cout << "Destroying " << name() << ", a video" << endl;
    }

private:
    int m_seconds;
    
};

class Picture: public File
{
public:
    Picture(string name)
    :File(name) {}
    
    virtual void open() const
    {
        cout << "show picture";
    }
    virtual void redisplay() const
    {
        cout << "refresh the screen";
    }
    virtual ~Picture()
    {
        cout << "Destroying the picture " << name() << endl;
    }
};

