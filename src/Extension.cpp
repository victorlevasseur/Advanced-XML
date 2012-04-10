/**

AdvancedXML
Copyright (C) 2012 Victor Levasseur

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

*/

#include "GDL/ExtensionBase.h"
#include "GDL/Version.h"
#include "AdvancedXMLRefManager.h"
#include <boost/version.hpp>

/**
 * This class declare information about the extension.
 */
class Extension : public ExtensionBase
{
    public:

        /**
         * Constructor of an extension declares everything the extension contains : Objects, actions, conditions and expressions.
         */
        Extension()
        {
            DECLARE_THE_EXTENSION("AdvancedXML",
                                  _("XML (avancé)"),
                                  _("Extension permettant de traiter des fichiers XML."),
                                  "Victor Levasseur",
                                  "Propriétaire")

            #if defined(GD_IDE_ONLY)

            DECLARE_ACTION("NewFile",
                           _("Créer un document XML"),
                           _("Crée un document XML."),
                           _("Créer un document XML en tant que _PARAM0_"),
                           _("XML avancé : Documents"),
                           "res/AdvancedXML/AdvancedXML.png",
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("string", _("Référence (permet d'accéder directement à l'élément plus tard)"), "", false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::CreateNewDocument").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("LoadFile",
                           _("Charger un fichier XML"),
                           _("Charge un fichier XML."),
                           _("Charger le fichier XML _PARAM0_ en tant que _PARAM1_"),
                           _("XML avancé : Documents"),
                           "res/AdvancedXML/AdvancedXML.png",
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("file", _("Fichier source"), "", false);
                instrInfo.AddParameter("string", _("Référence (permet d'accéder directement à l'élément plus tard)"), "", false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::LoadXmlFile").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("SaveFile",
                           _("Sauvegarder un fichier XML"),
                           _("Sauvegarde un fichier XML."),
                           _("Sauvegarder le fichier XML _PARAM1_ dans _PARAM0_"),
                           _("XML avancé : Documents"),
                           "res/AdvancedXML/AdvancedXML.png",
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("file", _("Fichier où enregistrer le fichier"), "", false);
                instrInfo.AddParameter("string", _("Référence sur le document XML"), "", false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::SaveXmlFile").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("BrowseTo",
                           _("Charger un élément dans une référence"),
                           _("Charge un élément (relatif à un autre) dans une référence.\nNote : les références permettent d'accéder à un élément grâce au nom de la référence."),
                           _("Charger le chemin _PARAM2_ relatif à _PARAM0_ dans la référence _PARAM0_"),
                           _("XML avancé : Général"),
                           "res/AdvancedXML/AdvancedXML.png",
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("string", _("Référence d'un élément existant (le chemin de l'élément sera relatif à cet élément)"), "", false);
                instrInfo.AddParameter("string", _("Nom de la référence à créer sur le futur élément"), "", false);
                instrInfo.AddParameter("string", _("Chemin (séparé par / , * pour prendre le 1er élément enfant sans savoir le nom de la balise)"), "", false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::BrowseTo").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("NextSibling",
                           _("Aller sur l'élément suivant"),
                           _("Crée une référence sur un élément suivant d'un élément.\nNote : L'élément récupéré sera invalide s'il n'existe pas : il est conseillé de tester son existance avec la condition."),
                           _("Charger l'élément _PARAM2_ suivant _PARAM1_ dans la référence _PARAM0_)"),
                           _("XML avancé : Général"),
                           "res/AdvancedXML/AdvancedXML.png",
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("string", _("Référence à créer"), "", false);
                instrInfo.AddParameter("string", _("Référence vers l'élément dont on doit récupérer l'élément suivant"), "", false);
                instrInfo.AddParameter("string", _("Filtrer par un nom de balise"), "", true);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::NextSibling").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h");

            DECLARE_END_ACTION()

            DECLARE_CONDITION("IsRefValid",
                           _("La référence est valide"),
                           _("Est valide uniquement si la référence est sur un élément existant et valide."),
                           _("_PARAM0_ est valide"),
                           _("XML avancé : Général"),
                           "res/AdvancedXML/AdvancedXML.png",
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("string", _("Référence vers l'élément à tester"), "", false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::IsRefValid").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h");

            DECLARE_END_CONDITION()

            DECLARE_ACTION("CreateNewElement",
                           _("Créer une nouvel élément"),
                           _("Crée un nouvel élément.\nNote : les références permettent d'accéder à un élément grâce au nom de la référence."),
                           _("Créer un élément en tant que _PARAM0_ de type _PARAM1_"),
                           _("XML avancé : Général"),
                           "res/AdvancedXML/AdvancedXML.png",
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("string", _("Référence sur l'élément (permettant d'accéder ultérieurement à l'élément)"), "", false);
                instrInfo.AddParameter("expression", _("Type d'élément à créer\n(0 -> Balise; 1 -> Texte; 2 -> Commentaire)"), "", false);
                instrInfo.AddParameter("string", _("Texte de l'élément\nSi c'est une balise, ce sera le nom de la balise, \nsi c'est un texte ou un commentaire, ce sera le texte"), "", false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::CreateNewElement").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("DeleteAnElement",
                           _("Supprimer un élément"),
                           _("Supprime un élément (l'élément sera retiré de son élément parent et détruit)."),
                           _("Supprimer l'élément _PARAM0_"),
                           _("XML avancé : Général"),
                           "res/AdvancedXML/AdvancedXML.png",
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("string", _("Référence sur l'élément à supprimer"), "", false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::DeleteAnElement").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h");

            DECLARE_END_ACTION()

            DECLARE_ACTION("InsertElementIntoAnother",
                           _("Ajouter un élément dans un autre"),
                           _("Ajoute un élément dans un autre. L'élément deviendra un \"enfant\" de son élément \"parent\"."),
                           _("Ajouter _PARAM0_ en tant qu'enfant de _PARAM1_ (avant _PARAM2_)"),
                           _("XML avancé : Balise"),
                           "res/AdvancedXML/AdvancedXML.png",
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("string", _("Référence sur l'élément à ajouter (n'importe quel type)"), "", false);
                instrInfo.AddParameter("string", _("Référence sur l'élément qui le contiendra (doit être une balise)"), "", false);
                instrInfo.AddParameter("string", _("L'élément sera ajouté avant l'élément (si non défini, l'élément sera ajouté à la fin)"), "", true);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::InsertElementIntoAnother").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h");

            DECLARE_END_ACTION()

            DECLARE_EXPRESSION("GetAttributeNumber",
                           _("Valeur d'un attribut d'un élément"),
                           _("Récupère la valeur d'un attribut d'un élément"),
                           _("XML avancé : Balise"),
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("string", _("Référence de l'élément"), "", false);
                instrInfo.AddParameter("string", _("Nom de l'attribut"), "", false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::GetAttributeNumber").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h");

            DECLARE_END_EXPRESSION()

            DECLARE_ACTION("SetAttributeNumber",
                           _("Changer la valeur d'un attribut"),
                           _("Change la valeur d'un attribut d'un élément (qui doit être une balide)."),
                           _("Faire _PARAM3__PARAM2_ à l'attribut _PARAM1_ de _PARAM0_"),
                           _("XML avancé : Balise"),
                           "res/AdvancedXML/AdvancedXML.png",
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("string", _("Référence sur l'élément"), "", false);
                instrInfo.AddParameter("string", _("Nom de l'attribut"), "", false);
                instrInfo.AddParameter("expression", _("Valeur"), "", false);
                instrInfo.AddParameter("operator", _("Signe de modification"), "", false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::SetAttributeNumber").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h").SetAssociatedGetter("AdvancedXML::GetAttributeNumber").SetManipulatedType("number");

            DECLARE_END_ACTION()

            DECLARE_STR_EXPRESSION("GetAttributeString",
                           _("Texte d'un attribut d'un élément"),
                           _("Récupère le texte d'un attribut d'un élément"),
                           _("XML avancé : Balise"),
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("string", _("Référence de l'élément"), "", false);
                instrInfo.AddParameter("string", _("Nom de l'attribut"), "", false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::GetAttributeString").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h");

            DECLARE_END_STR_EXPRESSION()

            DECLARE_ACTION("SetAttributeString",
                           _("Changer le texte d'un attribut"),
                           _("Change le texte d'un attribut d'un élément (qui doit être une balide)."),
                           _("Faire _PARAM3__PARAM2_ à l'attribut _PARAM1_ de _PARAM0_"),
                           _("XML avancé : Balise"),
                           "res/AdvancedXML/AdvancedXML.png",
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("string", _("Référence sur l'élément"), "", false);
                instrInfo.AddParameter("string", _("Nom de l'attribut"), "", false);
                instrInfo.AddParameter("string", _("Valeur"), "", false);
                instrInfo.AddParameter("operator", _("Signe de modification"), "", false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::SetAttributeString").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h").SetAssociatedGetter("AdvancedXML::GetAttributeString").SetManipulatedType("string");

            DECLARE_END_ACTION()

            DECLARE_ACTION("RemoveAttribute",
                           _("Supprimer un attribut"),
                           _("Supprime un attribut d'un élément (qui doit être une balide)."),
                           _("Supprimer l'attribut _PARAM1_ de _PARAM0_"),
                           _("XML avancé : Balise"),
                           "res/AdvancedXML/AdvancedXML.png",
                           "res/AdvancedXML/AdvancedXML16.png");

                instrInfo.AddParameter("string", _("Référence sur l'élément"), "", false);
                instrInfo.AddParameter("string", _("Nom de l'attribut"), "", false);
                instrInfo.AddCodeOnlyParameter("currentScene", "");

                instrInfo.cppCallingInformation.SetFunctionName("AdvancedXML::RemoveAttribute").SetIncludeFile("AdvancedXML/AdvancedXMLTools.h");

            DECLARE_END_ACTION()

            #endif

            CompleteCompilationInformation();
        };
        virtual ~Extension()
        {
            AdvancedXML::RefManager::Destroy();
        };

    protected:
    private:

        /**
         * This function is called by Game Develop so
         * as to complete information about how the extension was compiled ( which libs... )
         * -- Do not need to be modified. --
         */
        void CompleteCompilationInformation()
        {
            #if defined(GD_IDE_ONLY)
            compilationInfo.runtimeOnly = false;
            #else
            compilationInfo.runtimeOnly = true;
            #endif

            #if defined(__GNUC__)
            compilationInfo.gccMajorVersion = __GNUC__;
            compilationInfo.gccMinorVersion = __GNUC_MINOR__;
            compilationInfo.gccPatchLevel = __GNUC_PATCHLEVEL__;
            #endif

            compilationInfo.boostVersion = BOOST_VERSION;

            compilationInfo.sfmlMajorVersion = 2;
            compilationInfo.sfmlMinorVersion = 0;

            #if defined(GD_IDE_ONLY)
            compilationInfo.wxWidgetsMajorVersion = wxMAJOR_VERSION;
            compilationInfo.wxWidgetsMinorVersion = wxMINOR_VERSION;
            compilationInfo.wxWidgetsReleaseNumber = wxRELEASE_NUMBER;
            compilationInfo.wxWidgetsSubReleaseNumber = wxSUBRELEASE_NUMBER;
            #endif

            compilationInfo.gdlVersion = RC_FILEVERSION_STRING;
            compilationInfo.sizeOfpInt = sizeof(int*);

            compilationInfo.informationCompleted = true;
        }
};

/**
 * Used by Game Develop to create the extension class
 * -- Do not need to be modified. --
 */
extern "C" ExtensionBase * GD_EXTENSION_API CreateGDExtension() {
    return new Extension;
}

/**
 * Used by Game Develop to destroy the extension class
 * -- Do not need to be modified. --
 */
extern "C" void GD_EXTENSION_API DestroyGDExtension(ExtensionBase * p) {
    delete p;
}
