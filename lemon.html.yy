%include
{ 
	/**
	 * This file is part of Sodium Language project
	 *
	 * Copyright � 2020 Murad Karaka� <muradkarakas@gmail.com>
	 *
	 * This program is free software; you can redistribute it and/or
	 * modify it under the terms of the GNU General Public License v3.0
	 * as published by the Free Software Foundation; either
	 * version 3 of the License, or (at your option) any later version.
	 *
	 *	https://choosealicense.com/licenses/gpl-3.0/
	 */

#include <stdint.h>
#include "html.parser.imp.h"

#include <assert.h>

}

%name htmlParse

%extra_argument { SodiumCompiler *session }

%token_type { Token }

%syntax_error {
    printf("\nsyntax error");
    /*HTSQLPage *page = GetCurrentPage(session);
	char lineStr[10];
	sprintf_s(lineStr, sizeof(lineStr), "%d", session->sessionDebugInfo->lineNumberOuter);
    char *errMsg = mkStrcat(session->heapHandle, __FILE__, __LINE__, "HTML Syntax Error on line ", lineStr, ". Possible Tokens : (", NULL);
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    for (int i = 0; i < n; ++i) {
            int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
            if (a < YYNSTATE + YYNRULE) {
                char *tmp = mkStrcat(session->heapHandle, __FILE__, __LINE__, errMsg, " ", yyTokenName[i], NULL);
                mkFree(session->heapHandle, errMsg);
                errMsg = tmp;
            }
    }
    char *tempMsg = mkStrcat(session->heapHandle, __FILE__, __LINE__, errMsg, ")", NULL);
    mkFree(session->heapHandle, errMsg);
    errMsg = tempMsg;
	__sendErrorResponse(session, page, errMsg, "");
	CLOG(ERR_SYNTAX_ERROR_IN_FRMX_FILE, errMsg);*/
}

%token_destructor {
    if ($$.tokenStr != NULL) {
        printf("%s", $$.tokenStr);
        mkFree(session->heapHandle, $$.tokenStr);
        $$.tokenStr = NULL;
    }
}

start ::= expressions.

expressions ::= expressions expression.
expressions ::= expression.

expressions  ::= tagdoctype taghtml.
expressions  ::= taghtml.
expression   ::= space.
expression   ::= endoffile.

endoffile      ::= HTML_END_OF_FILE.

taghtmlcontents ::= tagbody.
taghtmlcontents ::= taghead tagbody.

tagheadcontents ::= tagheadcontents tagheadcontent.
tagheadcontents ::= tagheadcontent.

tagheadcontent  ::= tagtitle.
tagheadcontent  ::= tagscript.
tagheadcontent  ::= tagstyle.
tagheadcontent  ::= taglink.
tagheadcontent  ::= tagmeta.

tagbodycontents ::= tagbodycontents tagbodycontent.
tagbodycontents ::= tagbodycontent.

tagbodycontent  ::= htsqls.
tagbodycontent  ::= tagtable.
tagbodycontent  ::= space.
tagbodycontent  ::= htmltext.

htsqls ::= tagconnection.
htsqls ::= tagdatablock.
htsqls ::= tagcontrolblock.
htsqls ::= tagdatalist.

tagdoctype ::= TAG_DOCTYPE_HTSQL_DTD.
{
	
}
tagdoctype ::= TAG_DOCTYPE_HTML.
{
	
}

/** ############################################################################################
    HT/SQL Tree
    ############################################################################################
*/
tagtree                 ::= tagtreefullopen tagtreeblockclosefull.
tagtreefullopen         ::= tagtreeopen tagtreeproperties tagclosechar.
tagtreefullopen         ::= tagtreeopen tagtreeproperties tagclosechar spaces.

tagtreeopen             ::= TAG_TREE_OPEN(A).
{
    
}

tagtreeblockclosefull   ::= TAG_TREE_BLOCK_CLOSE(A).
{
    
}

tagtreeproperties       ::= tagtreeproperties tagtreeproperty.
tagtreeproperties       ::= tagtreeproperty.

tagtreeproperty         ::= tagtreepropertyid PROPERTYDATA.

tagtreepropertyid       ::= SPACE PROP_TREE_NAME ASSIGMENT.

/** ############################################################################################
    HT/SQL Datalist
    ############################################################################################
*/
tagdatalist           ::= tagdatalistfullopen tagdatalistblockclosefull.
tagdatalistfullopen   ::= tagdatalistopen datalistproperties tagclosechar.
tagdatalistfullopen   ::= tagdatalistopen datalistproperties tagclosechar spaces.

tagdatalistopen       ::= TAG_DATALIST_OPEN.
{
    
}

tagdatalistblockclosefull ::= tagdatalistblockclose.

tagdatalistblockclose ::= TAG_DATALIST_BLOCK_CLOSE.
{
    
}
datalistproperties   ::= datalistproperties datalistproperty.
datalistproperties   ::= datalistproperty.

datalistproperty     ::= tagdatalistpropertyid PROPERTYDATA(A).
{
    
}
tagdatalistpropertyid ::= SPACE PROP_DATALIST_DATALIST_NAME ASSIGMENT.

datalistproperty     ::= tagdatalistpropertyconnectionname PROPERTYDATA(A).
{
    
}
tagdatalistpropertyconnectionname ::= SPACE PROP_DATALIST_CONNECTION_NAME ASSIGMENT.



/** ############################################################################################
    HT/SQL Connection
    ############################################################################################
*/
tagconnection           ::= tagconnectionfullopen tagconnectionblockclosefull.
{
    
}
tagconnectionfullopen   ::= tagconnectionopen connectionproperties tagclosechar.
tagconnectionfullopen   ::= tagconnectionopen connectionproperties tagclosechar spaces.

tagconnectionopen       ::= TAG_CONNECTION_OPEN.
{
   
}

tagconnectionblockclosefull ::= tagconnectionblockclose.

tagconnectionblockclose ::= TAG_CONNECTION_BLOCK_CLOSE.
{

}
connectionproperties   ::= connectionproperties connectionproperty.
connectionproperties   ::= connectionproperty.

connectionproperty     ::= connectionpropertyconnectionname PROPERTYDATA(A).
{
   
}
connectionpropertyconnectionname ::= SPACE PROP_CONNECTION_CONNECTION_NAME  ASSIGMENT.

connectionproperty          ::=  connectionpropertyusername PROPERTYDATA(A).
{
    
}
connectionpropertyusername  ::= SPACE(A) PROP_CONNECTION_USER_NAME(B)  ASSIGMENT(C).
{
    
}

connectionproperty          ::=  connectionpropertyuserpassword PROPERTYDATA(A).
{
    
}
connectionpropertyuserpassword ::= SPACE(A) PROP_CONNECTION_USER_PASSWORD(B) ASSIGMENT(C).
{
    
}

connectionproperty     ::= connectionpropertyinstancename PROPERTYDATA(A).
{
   
}
connectionpropertyinstancename ::= SPACE PROP_CONNECTION_INSTANCE_NAME ASSIGMENT.


/** ############################################################################################
    HT/SQL Control Block
    ############################################################################################
*/
tagcontrolblock          ::= tagcontrolblockfullopen tagcontrolblockclosefull.
tagcontrolblock          ::= tagcontrolblockfullopen tagcontrolblockcontents tagcontrolblockclosefull.

tagcontrolblockfullopen  ::= tagcontrolblockopen tagcontrolblockproperties tagclosechar.

tagcontrolblockopen      ::= TAG_CONTROLBLOCK_OPEN.

tagcontrolblockclosefull ::= tagcontrolblockblockclose.
tagcontrolblockblockclose::= TAG_CONTROLBLOCK_CLOSE.

tagcontrolblockcontents  ::= tagcontrolblockcontents tagcontrolblockcontent.
tagcontrolblockcontents  ::= tagcontrolblockcontent.

tagcontrolblockcontent  ::= tagtree.
tagcontrolblockcontent  ::= space.
tagcontrolblockcontent  ::= htmltext.

tagcontrolblockproperties   ::= tagcontrolblockproperties tagcontrolblockproperty.

tagcontrolblockproperties   ::= tagcontrolblockproperty.

tagcontrolblockproperty     ::= SPACE(A) PROP_CONTROLBLOCK_BLOCK_NAME(B)  ASSIGMENT(C) PROPERTYDATA(NAME).
{
    
}
tagcontrolblockproperty     ::= SPACE PROPERTYID                    ASSIGMENT PROPERTYDATA.



/** ############################################################################################
    HT/SQL Data Block
    ############################################################################################
*/
tagdatablock           ::= tagdatablockfullopen tagdatablockblockclosefull.
tagdatablock           ::= tagdatablockfullopen tagdatablockcontents tagdatablockblockclosefull.
tagdatablockfullopen   ::= tagdatablockopen tagdatablockproperties tagclosechar.
{
    
}
tagdatablockopen       ::= TAG_DATABLOCK_OPEN.
{
    
}
tagdatablockblockclosefull ::= tagdatablockblockclose.

tagdatablockblockclose ::= TAG_DATABLOCK_BLOCK_CLOSE(A).
{
    
}

tagdatablockcontents ::= tagdatablockcontents tagdatablockcontent.
tagdatablockcontents ::= tagdatablockcontent.

tagdatablockcontent  ::= tagtable.
tagdatablockcontent  ::= space.
tagdatablockcontent  ::= htmltext.

tagdatablockproperties   ::= tagdatablockproperties tagdatablockproperty.

tagdatablockproperties   ::= tagdatablockproperty.

tagdatablockproperty     ::= SPACE PROPERTYID  ASSIGMENT PROPERTYDATA.

tagdatablockproperty     ::=  tagdatablockpropertyjoincondition PROPERTYDATA(B).
{
    
}
tagdatablockpropertyjoincondition ::= SPACE PROP_BLOCK_JOIN_CONDITION(A) ASSIGMENT(B).
{

}

tagdatablockproperty     ::=  tagdatablockpropertyconnectionname PROPERTYDATA(B).
{
   
}
tagdatablockpropertyconnectionname ::= SPACE PROP_BLOCK_CONNECTION_NAME(A) ASSIGMENT(B).
{

}

tagdatablockproperty     ::= tagdatablockpropertyautogeneratedcolumns PROPERTYDATA(B).
{
	
}
tagdatablockpropertyautogeneratedcolumns ::= SPACE PROP_BLOCK_AUTO_GENERATED_COLUMNS ASSIGMENT.

tagdatablockproperty     ::=  tagdatablockpropertyrecordcount PROPERTYDATA(B).
{
    
}
tagdatablockpropertyrecordcount ::= SPACE PROP_BLOCK_RECORD_COUNT ASSIGMENT.

tagdatablockproperty     ::=  tagdatablockpropertysourcename PROPERTYDATA(B).
{
    
}
tagdatablockpropertysourcename ::= SPACE PROP_BLOCK_DATA_SOURCE_NAME(A) ASSIGMENT(B).
{
	
}

tagdatablockproperty     ::= tagdatablockpropertyschemaname PROPERTYDATA(B).
{
	
}
tagdatablockpropertyschemaname ::= SPACE PROP_BLOCK_DATA_SCHEMA_NAME(A) ASSIGMENT(B).
{
	
}

tagdatablockproperty     ::=  tagdatablockpropertyblockname PROPERTYDATA(B).
{
   
}
tagdatablockpropertyblockname ::= SPACE PROP_BLOCK_BLOCK_NAME ASSIGMENT.

tagdatablockproperty     ::=  tagdatablockpropertykeycolumnname PROPERTYDATA(B).
{
    
}
tagdatablockpropertykeycolumnname ::= SPACE PROP_BLOCK_KEY_COLUMN_NAME ASSIGMENT.

tagdatablockproperty     ::=  tagdatablockpropertymasterblockname PROPERTYDATA(B).
{
    
}
tagdatablockpropertymasterblockname ::= SPACE PROP_BLOCK_MASTER_BLOCK_NAME ASSIGMENT.

tagdatablockproperty     ::= tagdatablockpropertyinsertallowed PROPERTYDATA(B).
{
    
}
tagdatablockpropertyinsertallowed ::= SPACE PROP_BLOCK_INSERT_ALLOWED ASSIGMENT.

tagdatablockproperty    ::= tagdatablockpropertydeleteallowed PROPERTYDATA(B).
{
    
}
tagdatablockpropertydeleteallowed ::= SPACE PROP_BLOCK_DELETE_ALLOWED ASSIGMENT.

tagdatablockproperty     ::= tagdatablockpropertyupdateallowed PROPERTYDATA(B).
{
    
}
tagdatablockpropertyupdateallowed ::= SPACE PROP_BLOCK_UPDATE_ALLOWED ASSIGMENT.


tagdatablockproperty     ::= tagdatablockpropertywhereclause PROPERTYDATA(B).
{
    
}
tagdatablockpropertywhereclause ::= SPACE PROP_BLOCK_WHERE_CLAUSE(A) ASSIGMENT(B).
{

}

tagdatablockproperty    ::=  tagdatablockpropertyorderbyclause PROPERTYDATA(B).
{
    
}
tagdatablockpropertyorderbyclause ::= SPACE PROP_BLOCK_OREDERBY_CLAUSE(A) ASSIGMENT(B).
{
	
}


/** ############################################################################################
    HT/SQL Input & Select
    ############################################################################################
*/
taginput           ::= taginputfullopen.
taginput           ::= taginputfullopen taginputblockclosefull.
taginputfullopen   ::= taginputopen taginputproperties tagclosechar.
taginputfullopen   ::= taginputopen taginputproperties taginputshortclose.


taginputshortclose ::= TAG_SHORT_CLOSE.
{
	
}

taginputopen       ::= TAG_INPUT_OPEN(A).
{
    
}
taginputopen       ::= TAG_SELECT_OPEN(A).
{
    
}
taginputopen       ::= TAG_TEXTAREA_OPEN(A).
{

}
taginputblockclosefull ::= taginputblockclose.
{
  
}
taginputblockclose ::= TAG_INPUT_BLOCK_CLOSE(A).
{

}

taginputblockclose ::= TAG_SELECT_BLOCK_CLOSE(A).
{

}

taginputblockclose ::= TAG_TEXTAREA_BLOCK_CLOSE(A).
{
    
}



taginputproperties    ::= taginputproperties taginputproperty.

taginputproperties    ::= taginputproperty.

taginputproperty      ::= taginputcheckedvalue PROPERTYDATA(B).
{
    
}
taginputcheckedvalue   ::= spaces PROP_INPUT_CHECKED_VALUE   ASSIGMENT.

taginputproperty      ::= taginputuncheckedvalue PROPERTYDATA(B).
{
    
}
taginputuncheckedvalue   ::= spaces PROP_INPUT_UNCHECKED_VALUE   ASSIGMENT.

taginputproperty      ::= taginputpropertyinputname PROPERTYDATA(B).
{
	
}
taginputpropertyinputname   ::= spaces PROP_INPUT_NAME   ASSIGMENT.

taginputproperty      ::= taginputpropertysequencename PROPERTYDATA(B).
{
    
}
taginputpropertysequencename   ::= spaces PROP_INPUT_SEQUENCE_NAME   ASSIGMENT.

taginputproperty      ::= taginputpropertysequenceschemaname PROPERTYDATA(B).
{
    
}
taginputpropertysequenceschemaname   ::= spaces PROP_INPUT_SEQUENCE_SCHEMA_NAME   ASSIGMENT.


taginputproperty      ::= taginputpropertymasteritemname PROPERTYDATA(B).
{
    
}
taginputpropertymasteritemname   ::= spaces PROP_INPUT_MASTER_ITEM_NAME ASSIGMENT.

taginputproperty            ::=  taginputpropertyinputtype PROPERTYDATA(B).
{
    
}
taginputpropertyinputtype   ::= spaces PROP_INPUT_TYPE  ASSIGMENT.

taginputproperty            ::= taginputpropertyinputvalue PROPERTYDATA(B).
{
    
}
taginputpropertyinputvalue  ::= spaces PROP_INPUT_VALUE ASSIGMENT.


taginputproperty            ::= taginputpropertydefaultvalue PROPERTYDATA(B).
{
    
}
taginputpropertydefaultvalue::= spaces PROP_INPUT_DEFAULT_VALUE ASSIGMENT.

taginputproperty       ::=  taginputpropertycolumnname PROPERTYDATA(B).
{
    
}
taginputpropertycolumnname ::= spaces PROP_INPUT_COLUMN_NAME ASSIGMENT.

taginputproperty       ::= taginputpropertyformatmask PROPERTYDATA(B).
{
    
}
taginputpropertyformatmask ::= spaces PROP_INPUT_FORMAT_MASK ASSIGMENT.

taginputproperty       ::= taginputpropertydatatype PROPERTYDATA(B).
{
    
}
taginputpropertydatatype ::= spaces PROP_INPUT_DATA_TYPE ASSIGMENT.

taginputproperty       ::= taginputpropertymaxlength PROPERTYDATA(B).
{
    
}
taginputpropertymaxlength ::= spaces PROP_INPUT_MAX_LENGTH ASSIGMENT.

taginputproperty       ::= taginputpropertyinsertallowed PROPERTYDATA(B).
{
    
}
taginputpropertyinsertallowed ::= spaces PROP_INPUT_INSERT_ALLOWED   ASSIGMENT.

taginputproperty       ::= taginputpropertyupdateallowed PROPERTYDATA(B).
{
    
}
taginputpropertyupdateallowed ::= spaces PROP_INPUT_UPDATE_ALLOWED ASSIGMENT.

taginputproperty       ::= taginputpropertydatalistname PROPERTYDATA(B).
{

}
taginputpropertydatalistname ::= spaces PROP_INPUT_DATALIST_NAME ASSIGMENT.

taginputproperty       ::= taginputpropertylookupitemname PROPERTYDATA(B).
{
   
}
taginputpropertylookupitemname ::= spaces PROP_INPUT_LOOKUP_ITEM_NAME ASSIGMENT.

taginputproperty       ::= taginputpropertylookupitemblockname PROPERTYDATA(B).
{
	
}
taginputpropertylookupitemblockname ::= spaces PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME ASSIGMENT.

taginputproperty              ::= spaces PROPERTYID(A) ASSIGMENT(B) PROPERTYDATA(C).
{
    
}

/** ############################################################################################
    <table> ... </table>
    ############################################################################################
*/
tagtable         ::= tagtablefullopen tagtableblockclosefull.
tagtable         ::= tagtablefullopen tablecontent tagtableblockclosefull.

tagtablefullopen ::= tagtableopen tagclosechar.
tagtablefullopen ::= tagtableopen tagclosechar spaces.
tagtablefullopen ::= tagtableopen tagproperties tagclosechar.
tagtablefullopen ::= tagtableopen tagproperties tagclosechar spaces.

tagtableopen        ::= TAG_TABLE_OPEN.
{
    
}
tagtableblockclosefull ::= tagtableblockclose.

tagtableblockclose  ::= TAG_TABLE_BLOCK_CLOSE.
{
    
}




tablecontent  ::= tagthead tagtbody tagtfoot.
tablecontent  ::= tagthead tagtfoot tagtbody.
tablecontent  ::= tagthead tagtbody.
tablecontent  ::= tagtbody tagtfoot.
tablecontent  ::= tagtbody.


/** ############################################################################################
    <thead> ... </thead>
    ############################################################################################
*/
tagthead            ::= tagtheadfullopen tagtheadblockclosefull.
tagthead            ::= tagtheadfullopen tagtablerows tagtheadblockclosefull.
tagtheadfullopen    ::= tagtheadopen tagclosechar.
tagtheadfullopen    ::= tagtheadopen tagclosechar spaces.
tagtheadfullopen    ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar.
tagtheadfullopen    ::= tagtheadopen tagpropertieswithreturnvaluesall tagclosechar spaces.
tagtheadopen        ::= TAG_THEAD_OPEN.
{
	
}
tagtheadblockclosefull ::= tagtheadblockclose.
tagtheadblockclosefull ::= tagtheadblockclose spaces.

tagtheadblockclose  ::= TAG_THEAD_BLOCK_CLOSE.
{
	
}


/** ############################################################################################
    <tfoot> ... </tfoot>
    ############################################################################################
*/
tagtfoot            ::= tagtfootfullopen tagtablerows tagtfootblockclosefull.
tagtfootfullopen    ::= tagtfootopen tagclosechar.
tagtfootfullopen    ::= tagtfootopen tagclosechar spaces.
tagtfootfullopen    ::= tagtfootopen tagproperties tagclosechar.
tagtfootfullopen    ::= tagtfootopen tagproperties tagclosechar spaces.
tagtfootopen        ::= TAG_TFOOT_OPEN.
{
	
}
tagtfootblockclosefull ::= tagtfootblockclose.
tagtfootblockclosefull ::= tagtfootblockclose spaces.

tagtfootblockclose  ::= TAG_TFOOT_BLOCK_CLOSE.
{
	
}


/** ############################################################################################
    <tbody> ... </tbody>
    ############################################################################################
*/
tagtbody            ::= tagtbodyfullopen tagtablerows tagtbodyblockclosefull.
tagtbodyfullopen    ::= tagtbodyopen tagclosechar.
tagtbodyfullopen    ::= tagtbodyopen tagclosechar spaces.
tagtbodyfullopen    ::= tagtbodyopen tagproperties tagclosechar.
tagtbodyfullopen    ::= tagtbodyopen tagproperties tagclosechar spaces.
tagtbodyopen        ::= TAG_TBODY_OPEN.
{
	
}
tagtbodyblockclosefull ::= tagtbodyblockclose.
tagtbodyblockclosefull ::= tagtbodyblockclose spaces.

tagtbodyblockclose  ::= TAG_TBODY_BLOCK_CLOSE.
{
	
}


/** ############################################################################################
    <tr> ... </tr>
    ############################################################################################
*/
tagtablerows ::= tagtablerows tagtablerow.
tagtablerows ::= tagtablerow.

tagtablerow         ::= tagtablerowfullopen tagtablecols tagtablerowblockclosefull.
tagtablerowfullopen ::= tagtablerowopen tagclosechar.
tagtablerowfullopen ::= tagtablerowopen tagclosechar spaces.
tagtablerowfullopen ::= tagtablerowopen tagpropertieswithreturnvaluesall tagclosechar.

tagtablerowopen        ::= TAG_TR_OPEN(A).
{
    
}
tagtablerowblockclosefull ::= tagtablerowblockclose.
tagtablerowblockclosefull ::= tagtablerowblockclose spaces.

tagtablerowblockclose  ::= TAG_TR_BLOCK_CLOSE.
{
    
}


tagtablecols ::= tagtablecols tagtablecol.
tagtablecols ::= tagtablecol.

tagtablecol ::= tagtablecoltd.
tagtablecol ::= tagtablecolth.

/** ############################################################################################
    <td> ... </td>
    ############################################################################################
*/
tagtablecoltd         ::= tagtablecoltdfullopen tagtablecoltdblockclosefull.
tagtablecoltd         ::= tagtablecoltdfullopen spaces tagtablecoltdblockclosefull.
tagtablecoltd         ::= tagtablecoltdfullopen spaces tagtable spaces tagtablecoltdblockclosefull.
tagtablecoltd         ::= tagtablecoltdfullopen tagtablecolcontents tagtablecoltdblockclosefull.
tagtablecoltd         ::= tagtablecoltdfullopen spaces tagtablecolcontents tagtablecoltdblockclosefull.
tagtablecoltdfullopen ::= tagtablecoltdopen tagclosechar.

tagtablecoltdfullopen ::= tagtablecoltdopen tagproperties tagclosechar.

tagtablecoltdopen        ::= TAG_TD_OPEN.
{
    
}
tagtablecoltdblockclosefull ::= tagtablecoltdblockclose.
tagtablecoltdblockclosefull ::= tagtablecoltdblockclose spaces.

tagtablecoltdblockclose  ::= TAG_TD_BLOCK_CLOSE.
{
    
}

tagtablecolcontents ::= tagtablecolcontents tagtablecolcontent.
tagtablecolcontents ::= tagtablecolcontent.

tagtablecolcontent  ::= taginput.
tagtablecolcontent  ::= taginput spaces.
tagtablecolcontent  ::= htmltext.
tagtablecolcontent  ::= htmltext spaces.
tagtablecolcontent  ::= tagtable.

/** ############################################################################################
    <th> ... </th>
    ############################################################################################
*/
tagtablecolth         ::= tagtablecolthfullopen tagtablecolthblockclosefull.
tagtablecolth         ::= tagtablecolthfullopen tagtablecolcontents tagtablecolthblockclosefull.
tagtablecolthfullopen ::= tagtablecolthopen tagclosechar.

tagtablecolthfullopen ::= tagtablecolthopen tagpropertieswithreturnvaluesall tagclosechar.

tagtablecolthopen        ::= TAG_TH_OPEN.
{
    
}
tagtablecolthblockclosefull ::= tagtablecolthblockclose.
tagtablecolthblockclosefull ::= tagtablecolthblockclose spaces.

tagtablecolthblockclose  ::= TAG_TH_BLOCK_CLOSE.
{
    
}


/** ############################################################################################
    <title> ... </title>
    ############################################################################################
*/
tagtitle            ::= tagtitlefullopen tagtitleblockclosefull.
tagtitle            ::= tagtitlefullopen htmlandspaces tagtitleblockclosefull.
tagtitlefullopen    ::= tagtitleopen tagclosechar.
tagtitlefullopen    ::= tagtitleopen tagproperties tagclosechar.
tagtitleblockclosefull  ::= tagtitleblockclose.
tagtitleblockclosefull  ::= tagtitleblockclose spaces.
tagtitleopen        ::= TAG_TITLE_OPEN.
tagtitleblockclose  ::= TAG_TITLE_BLOCK_CLOSE.

/** ############################################################################################
    <link></link>
    ############################################################################################
*/
taglink         ::= taglinkfullopen.
taglink         ::= taglinkfullopen taglinkblockclosefull.
taglinkfullopen ::= taglinkopen tagproperties tagclosechar.
taglinkfullopen ::= taglinkopen tagproperties tagshortclose.

taglinkblockclosefull ::= taglinkblockclose.
taglinkblockclosefull ::= taglinkblockclose spaces.

taglinkopen           ::= TAG_LINK_OPEN.
taglinkblockclose     ::= TAG_LINK_BLOCK_CLOSE.


/** ############################################################################################
    <meta></meta>
    ############################################################################################
*/
tagmeta         ::= tagmetafullopen.
tagmeta         ::= tagmetafullopen tagmetablockclosefull.
tagmetafullopen ::= tagmetaopen tagproperties tagclosechar.
tagmetafullopen ::= tagmetaopen tagproperties tagshortclose.

tagmetablockclosefull ::= tagmetablockclose.
tagmetablockclosefull ::= tagmetablockclose spaces.

tagmetaopen           ::= TAG_META_OPEN.
tagmetablockclose     ::= TAG_META_BLOCK_CLOSE.


/** ############################################################################################
    <style></style>
    ############################################################################################
*/
tagstyle         ::= tagstylefullopen tagstyleblockclosefull.
tagstyle         ::= tagstylefullopen htmlandspaces tagstyleblockclosefull.
tagstylefullopen ::= tagstyleopen tagclosechar.
tagstylefullopen ::= tagstyleopen tagstyleproperties tagclosechar.

tagstyleblockclosefull ::= tagstyleblockclose.

tagstyleblockclosefull ::= tagstyleblockclose spaces.
tagstyleopen           ::= TAG_STYLE_OPEN.
tagstyleblockclose     ::= TAG_STYLE_BLOCK_CLOSE.

/*******  style tag properties *************************/
tagstyleproperties  ::= tagstyleproperties tagstyleproperty.
tagstyleproperties  ::= tagstyleproperty.

tagstyleproperty    ::= space PROPERTYID_SCRIPT_SRC ASSIGMENT PROPERTYDATA.
tagstyleproperty    ::= space PROPERTYID_SCRIPT_TYPE ASSIGMENT PROPERTYDATA.
tagstyleproperty    ::= space PROPERTYID ASSIGMENT PROPERTYDATA.


/** ############################################################################################
    <script></script>
    ############################################################################################
*/
tagscript         ::= tagscriptfullopen tagscriptblockclosefull.
tagscript         ::= tagscriptfullopen htmlandspaces tagscriptblockclosefull.
tagscriptfullopen ::= tagscriptopen tagclosechar.
tagscriptfullopen ::= tagscriptopen tagscriptproperties tagclosechar.

tagscriptblockclosefull ::= tagscriptblockclose.
{
	
}
tagscriptblockclosefull ::= tagscriptblockclose spaces.
{
	
}
tagscriptopen           ::= TAG_SCRIPT_OPEN.
tagscriptblockclose     ::= TAG_SCRIPT_BLOCK_CLOSE.


/*******  script tag properties *************************/
tagscriptproperties  ::= tagscriptproperties tagscriptproperty.
tagscriptproperties  ::= tagscriptproperty.

tagscriptproperty    ::=  tagscriptpropertyscripttype PROPERTYDATA(C).
{
	
}
tagscriptpropertyscripttype ::= SPACE PROPERTYID_SCRIPT_TYPE ASSIGMENT.

tagscriptproperty ::= tagscriptpropertysrc PROPERTYDATA(C).
{
	
}
tagscriptpropertysrc ::= SPACE PROPERTYID_SCRIPT_SRC ASSIGMENT.

/** ############################################################################################
    <html> ... </html>
    ############################################################################################
*/
taghtml         ::= taghtmlfullopen taghtmlblockclosefull.
taghtml         ::= taghtmlfullopen taghtmlcontents taghtmlblockclosefull.
taghtmlfullopen ::= taghtmlopen tagclosechar.
taghtmlfullopen ::= taghtmlopen tagclosechar spaces.
taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar.
taghtmlfullopen ::= taghtmlopen tagproperties tagclosechar spaces.

taghtmlblockclosefull ::= taghtmlblockclose.

taghtmlopen       ::= TAG_HTML_OPEN.
{
	
}
taghtmlblockclose ::= TAG_HTML_BLOCK_CLOSE.


/** ############################################################################################
    <body> ... </body>
    ############################################################################################
*/

tagbody ::= tagbodyfullopen tagbodyblockclosefull.
tagbody ::= tagbodyfullopen tagbodycontents tagbodyblockclosefull.

tagbodyfullopen ::= tagbodyopen tagclosechar.
{

}
tagbodyfullopen ::= tagbodyopen tagproperties tagclosechar.

tagbodyblockclosefull ::= tagbodyblockclose.
tagbodyblockclosefull ::= tagbodyblockclose spaces.

tagbodyopen         ::= TAG_BODY_OPEN.

tagbodyblockclose   ::= TAG_BODY_BLOCK_CLOSE(A).
{
    
}

/** ############################################################################################
    <head> ... </head>
    ############################################################################################
*/

taghead ::= tagheadfullopen tagheadblockclosefull.
taghead ::= tagheadfullopen tagheadcontents tagheadblockclosefull.

tagheadfullopen ::= tagheadopen.
{
	
}

tagheadblockclosefull ::= tagheadblockclose.
tagheadblockclosefull ::= tagheadblockclose space.

tagheadopen         ::= TAG_HEAD_OPEN.
tagheadopen         ::= TAG_HEAD_OPEN space.

tagheadblockclose   ::= TAG_HEAD_BLOCK_CLOSE.


/*******  generic tag properties WITH return value *************************
 *   Return values are REQUIRED.
 *   This definitions return all properties and their values within a single string.
 *   Return values should be destroyed by caller by calling htmlDestructor deliberately
 */
tagpropertieswithreturnvaluesall    ::= tagpropertieswithreturnvalues.

tagpropertieswithreturnvalues       ::= tagpropertieswithreturnvalues tagpropertywithreturnvalue.

tagpropertieswithreturnvalues       ::= tagpropertywithreturnvalue.

tagpropertywithreturnvalue          ::= PROPERTYID ASSIGMENT PROPERTYDATA.


/*******  generic tag properties WITHOUT return value*************************
 *   Return values are NOT REQUIRED.
 *   Return values will be destroyed by htmlDestructor after reduce. And automatically displayed in the client browser otherwise specified.
 */
tagproperties  ::= tagproperties tagproperty.
tagproperties  ::= tagproperty.

tagproperty    ::= space PROPERTYID ASSIGMENT PROPERTYDATA.


/*******  shared non-terminals **************************/
tagclosechar    ::=  TAG_CLOSE.
tagclosechar    ::=  SPACE TAG_CLOSE.

tagshortclose	::= TAG_SHORT_CLOSE.

/**
 *      Generic HTMLTEXTs and SPACEs
 *
 *      Result should be free.
 */
htmlandspaces ::= htmlandspaces htmlandspace.
htmlandspaces ::= htmlandspace.

htmlandspace  ::= HTMLTEXT.
htmlandspace  ::= SPACE.

htmltext ::= HTMLTEXT.

/**
 *      SPACE
 *
 */
spaces ::= spaces space.
spaces ::= space.
space  ::= SPACE.


