#ifndef DDEFILEINTERFACE_H
#define DDEFILEINTERFACE_H
#include <QtCore/qobject.h>
#include <QString>
#include <QList>
#include <QFrame>
class QIcon;

class DdeFileInterface
{
public:
    virtual ~DdeFileInterface() {}
    
        /*!
         *  \fn  void additionalIcon(const AbstractFileInfoPointer &fileInfo, QList<QIcon> &icons)
         *  \brief 文件或目录 显示时，向文件或目录 图标上面增加小图标的功能
         *  \param[ in ] const QString &filename 相关的文件名
         *  \param[ out ] QList<QIcon> &icons 向icons中输出qicon, 就有相应的图标
         */ 
    virtual void additionalIcon(const QString &filename, QList<QIcon> &icons)
     {
         Q_UNUSED(filename);
         Q_UNUSED(icons);          
     }

        /*!
         *  \fn  void addExpandInfo( const QString &filename, QStringList &titleList, QList<QFrame *> &frames  )
         *  \brief 增加文件属性的扩展部分
         *  \param[ in ] const QString &filename 相关的文件名
         *  \param[ out ] QStringList &titleList  扩展属性的名字
         *  \param[ out ] QList<QFrame *> &frames 扩展属性的显示内容qframe
         */ 
    virtual void addExpandInfo( const QString &filename, QStringList &titleList, QList<QFrame *> &frames  )
    {
        Q_UNUSED(filename);
        Q_UNUSED(titleList);
        Q_UNUSED(frames); 
    }


        /*!
         *  \fn  void additionalMenu(const QString &filename, QVector<int> &actionKeys)
         *  \brief 文件或目录 一级右键的 菜单处理 
         *  \param[ in ] const QString &filename 相关的文件名
         *  \param[ out ] QVector<MenuAction> &actionKeys  向actionKeys中输出相关的值, 就有相应的右键的 菜单
         */ 
    virtual void additionalMenu(const QString &filename, QVector<int> &actionKeys)
    {
        Q_UNUSED(filename);
        Q_UNUSED(actionKeys);          
    }

    
        /*!
         *  \fn  void additionalSubMenu(const QString &filename, QMap<int, QVector<int> > &subActions)
         *  \brief 文件或目录 右键的 二级子菜单处理 
         *  \param[ in ] const QString &filename 相关的文件名
         *  \param[ out ] QMap<int, QVector<int> > &subActions 右键的 二级子菜单
         */ 
    virtual void additionalSubMenu(const QString &filename, QMap<int, QVector<int> > &subActions)
    {
        Q_UNUSED(filename);
        Q_UNUSED(subActions);          
    }


        /*!
         *  \fn  void additionalMenuInit( int cmd, QStringList &actionName)
         *  \brief 文件或目录 右键的 菜单的初始化处理，插件支持的菜单全部在此处初始化 
         *  \param[ in ] int cmd 当前插件的命令值起始的命令值
         *  \param[ out ] QStringList &actionName 返回起始值开始的菜单显示内容
         */ 
    virtual void additionalMenuInit( int cmd, QStringList &actionName)
    {
        Q_UNUSED(cmd);
        Q_UNUSED(actionName);          
    }

        /*!
         *  \fn  void callMenu(const QStringList & filenames, int cmd)
         *  \brief 文件或目录 右键的 菜单处理的回调函数 
         *  \param[ in ] const QStringList & filenames 当前右键操作的文件列表
         *  \param[ in ] int cmd 当前菜单的命令值
         *  \return 无
         */ 
    virtual void callMenu(const QStringList & filenames, int cmd)
    {
        Q_UNUSED( filenames );
        Q_UNUSED( cmd );
    }


        /*!
         *  \fn  int checkCmd( int cmd )
         *  \brief 测试当前命令值是否属于 当前的插件
         *  \param[ in ] int cmd 当前命令值
         *  \return 1 在 0 不在
         */ 
    inline int checkCmd( int cmd )
    {
        if( (cmd >= cmdMin) && ( cmd < cmdMax ) )
        {
            return 1;
        }
        else
        {
            return 0;
        }     
    }
    int cmdMin;  //!< 右键菜单值的最小值
    int cmdMax;  //!< 右键菜单值的最大值
    
};


QT_BEGIN_NAMESPACE
#define DdeFileInterface_iid "com.deepin.ddefileInterface"
Q_DECLARE_INTERFACE(DdeFileInterface, DdeFileInterface_iid)
QT_END_NAMESPACE


#endif
