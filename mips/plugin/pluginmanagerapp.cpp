#include "pluginmanagerapp.h"
#include <QtWidgets>
/*!
 * \file pluginmanagerapp.cpp
 * \author txx
 * \email  sailing_tang@163.com
 * \brief 插件管理及调用的类，本类只有一个全局对象的实例
 * \date 2016-09-27 13:11:09
 */


#define PLUGINSDIR  "/usr/share/dde-file-manager/plugins"

class QDir;


PluginManagerApp::PluginManagerApp(QObject *parent) : QObject(parent)
{
}

PluginManagerApp::~PluginManagerApp()
{

}

void PluginManagerApp::loadPlugin()
{
    QDir pluginsDir( PLUGINSDIR);
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin)
        {
            DdeFileInterface *ddefileInterface = qobject_cast<DdeFileInterface *>(plugin);
            if (ddefileInterface)
            {
                plugins.push_back( ddefileInterface );
                    // Unknow空出来，从它的后面开始
                ddefileInterface->additionalMenuInit( MenuAction::Unknow+1 + actionNames.size(  ), actionNames  ); 
            }
        }
    }
    qDebug(  ) << "loadPlugin size:" << plugins.size(  );
}

/**!
 *  \fn  void addPlugActionKeys()
 *  \brief 增加插件的右键盘菜单项的初始化
 *  \param[ out ] QMap<MenuAction, QString> &m_actionKeys 要返回的右键盘菜单项的值
 */ 
void PluginManagerApp::addPlugActionKeys(QMap<MenuAction, QString> &m_actionKeys)
{
    for( int i = 0; i < actionNames.size(  ); i++ )
    {
        MenuAction tmp = (MenuAction)(MenuAction::Unknow + 1 + i);
        m_actionKeys[tmp] = actionNames[ i ];
    }
}


/*!
 *  \fn  void fileAdditionalIcon(const AbstractFileInfoPointer &fileInfo, QList<QIcon> &icons)
 *  \brief 文件显示时，向文件图标上面增加小图标的功能
 *  \param[ in ] const AbstractFileInfoPointer &fileInfo 文件相关的信息
 *  \param[ out ] QList<QIcon> &icons 向icons中输出qicon, 就有相应的图标
 */ 
void PluginManagerApp::fileAdditionalIcon(const QString &filename, QList<QIcon> &icons)
{
    for( unsigned int i = 0; i < plugins.size(  ); i++ )
    {
        plugins[ i ]->additionalIcon( filename, icons );
    }
}

/**!
 *  \fn  void addExpandInfo( const QString &filename, QStringList &titleList, QList<QFrame *> &frames  )
 *  \brief 增加文件属性的扩展部分
 *  \param[ in ] const QString &filename 相关的文件名
 *  \param[ out ] QStringList &titleList  扩展属性的名字
 *  \param[ out ] QList<QFrame *> &frames 扩展属性的显示内容qframe
 */ 
void PluginManagerApp::addExpandInfo( const QString &filename, QStringList &titleList, QList<QFrame *> &frames  )
{
    for( unsigned int i = 0; i < plugins.size(  ); i++ )
    {
        plugins[ i ]->addExpandInfo( filename, titleList,frames );
    }   
}


/**!
 *  \fn  void additionalMenu(const QString &filename, QVector<int> &actionKeys)
 *  \brief 文件或目录 一级右键的 菜单处理 
 *  \param[ in ] const QString &filename 相关的文件名
 *  \param[ out ] QVector<MenuAction> &actionKeys  向actionKeys中输出相关的值, 就有相应的右键的 菜单
 */ 
void PluginManagerApp::additionalMenu(const QString &filename, QVector<MenuAction> &actionKeys )
{
    QVector<int> mykeys;
    for( unsigned int i = 0; i < plugins.size(  ); i++ )
    {
        plugins[ i ]->additionalMenu( filename, mykeys );
    }

    for( int i = 0; i < mykeys.size(  ); i++ )
    {
        MenuAction tmp = (MenuAction)mykeys[ i ];
        actionKeys << tmp;
    }
}

/**!
 *  \fn  void additionalSubMenu(const QString &filename, QMap<MenuAction, QVector<MenuAction> > &subActions)
 *  \brief 文件或目录 右键的 二级子菜单处理 
 *  \param[ in ] const QString &filename 相关的文件名
 *  \param[ out ] QMap<MenuAction, QVector<MenuAction> > &subActions 右键的 二级子菜单
 */ 
void PluginManagerApp::additionalSubMenu(const QString &filename, QMap<MenuAction, QVector<MenuAction> > &subActions )
{
    QMap<int, QVector<int> > mykeys;
    for( unsigned int i = 0; i < plugins.size(  ); i++ )
    {
        plugins[ i ]->additionalSubMenu( filename, mykeys );
    }

    QMap<int, QVector<int>>::const_iterator i = mykeys.constBegin();
    while (i != mykeys.constEnd())
    {
        MenuAction key = (MenuAction)i.key();
        QVector<MenuAction> actionKeys;

        QVector<int> myvalues =  i.value();
        for( int x = 0; x < myvalues.size(  ); x++ )
        {
            MenuAction tmp = (MenuAction)myvalues[ x ];
            actionKeys << tmp;
        }
        
        subActions.insert(key, actionKeys);

        ++i;
    }
}



/**!
 *  \fn  void callMenu(const QStringList & filenames, int cmd)
 *  \brief 文件或目录 右键的 菜单处理的回调函数 
 *  \param[ in ] const QStringList & filenames 当前右键操作的文件列表
 *  \param[ in ] int cmd 当前菜单的命令值
 *  \return 无
 */ 
void  PluginManagerApp::callMenu(const QStringList & filenames, int cmd)   
{
    int ret = 0;
    for( unsigned int i = 0; i < plugins.size(  ); i++ )
    {
        ret = plugins[ i ]->checkCmd(cmd);
        if( ret )
        {
            qDebug() << "cmd:" << cmd << " filename:"<< filenames;
            plugins[ i ]->callMenu( filenames, cmd );
            return;
        }
    }
}
