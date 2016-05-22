#ifndef EXCEPTION_H
#define EXCEPTION_H


class ComputerException {
    QString info;
public:
    ComputerException(const QString& str):info(str){}
    QString getInfo() const { return info; }
};



#endif // EXCEPTION_H
