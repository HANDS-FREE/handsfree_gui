#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

class CommandAvailable ;
class QString ;
class QTreeWidget ;

class CommandFactory
{
public:
    CommandFactory(){}
     virtual CommandAvailable* createNewCommand(const QString &command_name,QTreeWidget *target_widget) = 0 ;
};

#endif // COMMANDFACTORY_H
