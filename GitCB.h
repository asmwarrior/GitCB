/***************************************************************
 * Name:      gitcb
 * Purpose:   Code::Blocks plugin
 * Author:    icequan (jingquan233@gmail.com)
 * Created:   2017-03-05
 * Copyright: icequan
 * License:   GPL
 **************************************************************/

#ifndef GITCB_H_INCLUDED
#define GITCB_H_INCLUDED

// For compilers that support precompilation, includes <wx/wx.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <cbplugin.h>
// for "class cbPlugin"
class wxMenu;           //forward declare
class TextCtrlLogger;

class GitCB : public cbPlugin
{
    public:
        /** Constructor. */
        GitCB();
        /** Destructor. */
        virtual ~GitCB();

        /** This method is called by Code::Blocks and is used by the plugin
          * to add any menu items it needs on Code::Blocks's menu bar.\n
          * It is a pure virtual method that needs to be implemented by all
          * plugins. If the plugin does not need to add items on the menu,
          * just do nothing ;)
          * @param menuBar the wxMenuBar to create items in
          */
        virtual void BuildMenu(wxMenuBar* menuBar);

        /** This method is called by Code::Blocks core modules (EditorManager,
          * ProjectManager etc) and is used by the plugin to add any menu
          * items it needs in the module's popup menu. For example, when
          * the user right-clicks on a project file in the project tree,
          * ProjectManager prepares a popup menu to display with context
          * sensitive options for that file. Before it displays this popup
          * menu, it asks all attached plugins (by asking PluginManager to call
          * this method), if they need to add any entries
          * in that menu. This method is called.\n
          * If the plugin does not need to add items in the menu,
          * just do nothing ;)
          * @param type the module that's preparing a popup menu
          * @param menu pointer to the popup menu
          * @param data pointer to FileTreeData object (to access/modify the file tree)
          */
        virtual void BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data = 0);

        /** This method is called by Code::Blocks and is used by the plugin
          * to add any toolbar items it needs on Code::Blocks's toolbar.\n
          * It is a pure virtual method that needs to be implemented by all
          * plugins. If the plugin does not need to add items on the toolbar,
          * just do nothing ;)
          * @param toolBar the wxToolBar to create items on
          * @return The plugin should return true if it needed the toolbar, false if not
          */
        virtual bool BuildToolBar(wxToolBar* toolBar){ return false; }

        virtual cbConfigurationPanel* GetConfigurationPanel(wxWindow* parent){ return 0; }
    protected:
        /** Any descendent plugin should override this virtual method and
          * perform any necessary initialization. This method is called by
          * Code::Blocks (PluginManager actually) when the plugin has been
          * loaded and should attach in Code::Blocks. When Code::Blocks
          * starts up, it finds and <em>loads</em> all plugins but <em>does
          * not</em> activate (attaches) them. It then activates all plugins
          * that the user has selected to be activated on start-up.\n
          * This means that a plugin might be loaded but <b>not</b> activated...\n
          * Think of this method as the actual constructor...
          */
        virtual void OnAttach();
        /** Any descendent plugin should override this virtual method and
          * perform any necessary de-initialization. This method is called by
          * Code::Blocks (PluginManager actually) when the plugin has been
          * loaded, attached and should de-attach from Code::Blocks.\n
          * Think of this method as the actual destructor...
          * @param appShutDown If true, the application is shutting down. In this
          *         case *don't* use Manager::Get()->Get...() functions or the
          *         behaviour is undefined...
          */
        virtual void OnRelease(bool appShutDown);

    private:
        wxMenu* git;
        wxMenu* menu;
        wxMenu* currentrepository;
        wxMenu* remoterepository;
        wxMenu* gitmodule;
        TextCtrlLogger* gitcblogger;


        int  Execute        (const wxString& command);
        void commit         (wxCommandEvent& event);
        void push           (wxCommandEvent& event);
        void status         (wxCommandEvent& event);
        void setgitcb       (wxCommandEvent& event);
        void showclonedlg   (wxCommandEvent& event);
        void showcommitdlg  (wxCommandEvent& event);
        void showbranchdlg  (wxCommandEvent& event);
/**
estimate the project wheather is loaded or not,the C::B sdk has the implicit problem,do NOT use
project->isload() here,beacause the project will be a nullptr if you don't open a project,so CRASH
will coming :)
*/
        bool Is_loaded();

        int logSlot;
        int pullid          =wxNewId();
        int commitid        =wxNewId();
        int patchid         =wxNewId();
        int cloneid         =wxNewId();
        int pushid          =wxNewId();
        int newposid        =wxNewId();
        int branchid        =wxNewId();
        int initid          =wxNewId();
        int modulecommitid  =wxNewId();
        int modulecloneid   =wxNewId();
        int modulepushid    =wxNewId();
        int modulenewposid  =wxNewId();
        int modulebranchid  =wxNewId();
        int moduleinitid    =wxNewId();
        int modulestatusid  =wxNewId();

        DECLARE_EVENT_TABLE();
};

#endif // GITCB_H_INCLUDED
