#ifndef  PLUGINMANAGERAPP_H

#include "ddefileinterface.h"
/*!
 * \file pluginmanagerapp.cpp
 * \author txx
 * \email  sailing_tang@163.com
 * \brief 插件管理及调用的类，本类只有一个全局对象的实例
 * \date 2016-09-27 13:11:09
 */

#include <QFrame>
#include <vector>
#include "abstractfileinfo.h"

class PluginManagerApp : public QObject
{
    Q_OBJECT
    
  public:
    explicit PluginManagerApp(QObject *parent = 0);

    ~PluginManagerApp();

    void loadPlugin();


        /*!
         *  \fn  void fileAdditionalIcon(const AbstractFileInfoPointer &fileInfo, QList<QIcon> &icons)
         *  \brief 文件显示时，向文件图标上面增加小图标的功能
         *  \param[ in ] const AbstractFileInfoPointer &fileInfo 文件相关的信息
         *  \param[ out ] QList<QIcon> &icons 向icons中输出qicon, 就有相应的图标
         */ 
    void fileAdditionalIcon(const QString &filename, QList<QIcon> &icons);

        /**!
         *  \fn  void addExpandInfo( const QString &filename, QStringList &titleList, QList<QFrame *> &frames  )
         *  \brief 增加文件属性的扩展部分
         *  \param[ in ] const QString &filename 相关的文件名
         *  \param[ out ] QStringList &titleList  扩展属性的名字
         *  \param[ out ] QList<QFrame *> &frames 扩展属性的显示内容qframe
         */ 
    void addExpandInfo( const QString &filename, QStringList &titleList, QList<QFrame *> &frames  );


        /**!
         *  \fn  void addPlugActionKeys()
         *  \brief 增加插件的右键盘菜单项的初始化
         *  \param[ out ] QMap<MenuAction, QString> &m_actionKeys 要返回的右键盘菜单项的值
         */ 
    void addPlugActionKeys(QMap<MenuAction, QString> &m_actionKeys);
    
        /**!
         *  \fn  void additionalMenu(const QString &filename, QVector<int> &actionKeys)
         *  \brief 文件或目录 一级右键的 菜单处理 
         *  \param[ in ] const QString &filename 相关的文件名
         *  \param[ out ] QVector<MenuAction> &actionKeys  向actionKeys中输出相关的值, 就有相应的右键的 菜单
         */ 
    void additionalMenu(const QString &filename, QVector<MenuAction> &actionKeys);


        /**!
         *  \fn  void additionalSubMenu(const QString &filename, QMap<MenuAction, QVector<MenuAction> > &subActions)
         *  \brief 文件或目录 右键的 二级子菜单处理 
         *  \param[ in ] const QString &filename 相关的文件名
         *  \param[ out ] QMap<MenuAction, QVector<MenuAction> > &subActions 右键的 二级子菜单
         */ 
    void additionalSubMenu(const QString &filename, QMap<MenuAction, QVector<MenuAction> > &subActions );


        /**!
         *  \fn  void callMenu(const QStringList & filenames, int cmd)
         *  \brief 文件或目录 右键的 菜单处理的回调函数 
         *  \param[ in ] const QStringList & filenames 当前右键操作的文件列表
         *  \param[ in ] int cmd 当前菜单的命令值
         *  \return 无
         */ 
    void callMenu(const QStringList & filenames, int cmd);

  private:
    QStringList actionNames;  //!< 自定义的右键菜单显示的内容
    
  private:
    std::vector <DdeFileInterface *>plugins;
};





#endif
