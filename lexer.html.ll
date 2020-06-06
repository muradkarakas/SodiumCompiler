%{
/**
  * This file is part of Sodium Language project
  *
  * Copyright © 2020 Murad Karakaþ <muradkarakas@gmail.com>
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU General Public License v3.0
  * as published by the Free Software Foundation; either
  * version 3 of the License, or (at your option) any later version.
  *
  *	https://choosealicense.com/licenses/gpl-3.0/
  */

#include "pch.h"

#include "lemon.html.h"
#include "html.parser.imp.h"

%}

%top{
#include <stdint.h>
}

%option extra-type="SodiumCompiler *"
%option never-interactive
%option nounistd
%option reentrant
%option noyywrap noinput nounput

PARAOPEN		"{"*
PARACLOSE		"}"*
SPACE			[ \t]*
TAGCLOSECHAR	"\/"
HTMLTEXT        [.a-zA-Z#(),:;!=?'"0-9\t\n\{\}\]\-\\[/@$*+_\.]

bom     \xEF\xBB\xBF

u2a     [\xC2-\xDF][\x80-\xBF]
u2b     \xE0[\xA0-\xBF][\x80-\xBF]
u3a     [\xE1-\xEC\xEE\xEF][\x80-\xBF]{2}
u3b     \xED[\x80-\x9F][\x80-\xBF]
u4a     \xF0[\x90-\xBF][\x80-\xBF]{2}
u4b     [\xF1-\xF3][\x80-\xBF]{3}
u4c     \xF4[\x80-\x8F][\x80-\xBF]{2}

utf_8   {u2a}|{u2b}|{u3a}|{u3b}|{u4a}|{u4b}|{u4c}

%x SC_TAGPROPERTY
%x SC_HTML_TAGPROPERTY
%x SC_SCRIPTAG_PROPERTY
%x SC_INPUT_PROPERTIES
%x SC_TITLE
%x SC_HTML_COMMENT
%x SC_SCRIPT
%x SC_DATALIST_PROPERTIES
%x SC_DATABLOCK_PROPERTIES
%x SC_LOV_PROPERTIES
%x SC_TAGSCRIPTPROPERTY
%x SC_TAG_DATABLOCK_CONTENT
%x SC_HTSQL_TAGPROPERTY
%x SC_TREE_PROPERTIES

%x SC_TAG_CONTROLBLOCK_CONTENT
%x SC_CONTROLBLOCK_PROPERTIES

BEGIN(INITIAL);

%%

 /* ############################################################################################
    ############################################################################################

    BOM / FILE ENCODING 

    ############################################################################################
 */

{bom}	{ 
			// DO NOTHING FOR BOM
		}
{utf_8} { 
			// DO NOTHING FOR BOM  
		}

 /* ############################################################################################
    ############################################################################################

    HTML Tags

    ############################################################################################
 */

{SPACE}"<"{SPACE}"!DOCTYPE"{SPACE}"HTML"{SPACE}"SYSTEM"{SPACE}"\"ht-sql.dtd\""{SPACE}">"{SPACE}      {
                                                                                                        return TAG_DOCTYPE_HTSQL_DTD;
                                                                                                     }
{SPACE}"<"{SPACE}"!DOCTYPE"{SPACE}"html"{SPACE}">"{SPACE}											 {
																										return TAG_DOCTYPE_HTML;
																									 }
{SPACE}"<"{SPACE}"html"	                            {
                                                        BEGIN(SC_HTML_TAGPROPERTY);
                                                        return TAG_HTML_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"html"{SPACE}">"	    {
                                                        return TAG_HTML_BLOCK_CLOSE;
                                                    }
"<"{SPACE}"body"	                                {
                                                        BEGIN(SC_HTML_TAGPROPERTY);
                                                        return TAG_BODY_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"body"{SPACE}">"	    {
                                                        return TAG_BODY_BLOCK_CLOSE;
                                                    }
"<"{SPACE}"head"{SPACE}">"                          {                                                        
                                                        return TAG_HEAD_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"head"{SPACE}">"	    {
                                                        return TAG_HEAD_BLOCK_CLOSE;
                                                    }
"<"{SPACE}"title"	                                {
                                                        BEGIN(SC_HTML_TAGPROPERTY);
                                                        return TAG_TITLE_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"title"{SPACE}">"	{
														return TAG_TITLE_BLOCK_CLOSE;
													}
"<"{SPACE}"link"                                    {
                                                        BEGIN(SC_HTML_TAGPROPERTY);
                                                        return TAG_LINK_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"link"{SPACE}">"	    {
                                                        return TAG_LINK_BLOCK_CLOSE;
                                                    }
"<"{SPACE}"meta"                                    {
                                                        BEGIN(SC_HTML_TAGPROPERTY);
                                                        return TAG_META_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"meta"{SPACE}">"	    {
                                                        return TAG_META_BLOCK_CLOSE;
                                                    }
"<"{SPACE}"script"	                                {
                                                        BEGIN(SC_TAGSCRIPTPROPERTY);
                                                        return TAG_SCRIPT_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"script"{SPACE}">"	{
														return TAG_SCRIPT_BLOCK_CLOSE;
													}
"<"{SPACE}"style"	                                {
                                                        BEGIN(SC_TAGSCRIPTPROPERTY);
                                                        return TAG_STYLE_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"style"{SPACE}">"	{
														return TAG_STYLE_BLOCK_CLOSE;
													}
\n											        {
														SodiumCompiler *session = yyextra;
                                                        session->lineNumberOuter++;
                                                        return ENTER;
													}
{SPACE}                                             {
                                                        return SPACE;
                                                    }
<<EOF>>												{
														return END_OF_FILE;
													}
.                                                   {
                                                        return HTMLTEXT;
                                                    }


<SC_TAGSCRIPTPROPERTY>{
"src"                       {
                                return PROPERTYID_SCRIPT_SRC;
                            }
"type"                      {
                                return PROPERTYID_SCRIPT_TYPE;
                            }
[a-zA-Z_]([^\n\t <>=?;"'\(\)\[\]\{\}])*			{
													return PROPERTYID;
												}
"="     					{
								return ASSIGMENT;
							}
\"([^\"])*\"	            {
                                return PROPERTYDATA;
                            }
{SPACE}                     {
                                return SPACE;
                            }
">"						    {
                                BEGIN(INITIAL);
                                return TAG_CLOSE;
                            }
}


 /* ############################################################################################
    SC_HTML_TAGPROPERTY
    ############################################################################################
 */
<SC_HTML_TAGPROPERTY>{
[a-zA-Z_]([^\n\t <>=?;"'\(\)\[\]\{\}])*				{
														return PROPERTYID;
													}
{SPACE}"="{SPACE}   		                        {
                                                        return ASSIGMENT;
                                                    }
\"([^\"])*\"	                                    {
                                                        return PROPERTYDATA;

                                                    }
\n{SPACE}											{
														SodiumCompiler * session = yyextra;
                                                        session->lineNumberOuter++;
													}
{SPACE}                                             {
                                                        return SPACE;
                                                    }
{SPACE}"/"{SPACE}">"{SPACE}							{
														BEGIN(INITIAL); 
														return TAG_SHORT_CLOSE;
													}
">"						                            {
														BEGIN(INITIAL);
														return TAG_CLOSE;
                                                    }
}

 /* ############################################################################################
    HT/SQL Tree
    ############################################################################################
 */

<SC_TREE_PROPERTIES>{
"id"                    {
                            return PROP_TREE_NAME;
                        }
{SPACE}"="{SPACE}       {
                            return ASSIGMENT;
                        }
\"([^\"])*\"	        {
							return PROPERTYDATA;
						}
">"				        {
							BEGIN(SC_TAG_CONTROLBLOCK_CONTENT);
                            return TAG_CLOSE;
						}
{SPACE}                 {
                            return SPACE;
                        }
}

 /* ############################################################################################
    HT/SQL Datalist
    ############################################################################################
 */
"<"{SPACE}"datalist"	{
                            BEGIN(SC_DATALIST_PROPERTIES);
                            return TAG_DATALIST_OPEN;
                        }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"datalist"{SPACE}">"	{
                                                        BEGIN(INITIAL);
                                                        return TAG_DATALIST_BLOCK_CLOSE;
                                                    }
<SC_DATALIST_PROPERTIES>{
"id"                    {
                            return PROP_DATALIST_DATALIST_NAME;
                        }
"connection-name"       {
                            return PROP_DATALIST_CONNECTION_NAME;
                        }
{SPACE}"="{SPACE}       {
                            return ASSIGMENT;
                        }
\"([^\"])*\"	        {
							return PROPERTYDATA;
						}
">"				        {
							BEGIN(INITIAL);
                            return TAG_CLOSE;
						}
{SPACE}                 {
                            return SPACE;
                        }
}


 /* ############################################################################################
    HT/SQL Control Block
    ############################################################################################
 */
"<"{SPACE}"controlblock"	{
                                BEGIN(SC_CONTROLBLOCK_PROPERTIES);
                                return TAG_CONTROLBLOCK_OPEN;
                            }
<SC_CONTROLBLOCK_PROPERTIES>{
"control-block-name"    {
                            return PROP_CONTROLBLOCK_BLOCK_NAME;
                        }
[a-zA-Z_]([^\n\t <>=?;"'\(\)\[\]\{\}])*				{
														return PROPERTYID;
													}
{SPACE}"="{SPACE}		{
                            return ASSIGMENT;
                        }
\"([^\"])*\"	        {
                            return PROPERTYDATA;
                        }
">"				        {
							BEGIN(SC_TAG_CONTROLBLOCK_CONTENT);
                            return TAG_CLOSE;
						}
{SPACE}\n{SPACE}		{
                            SodiumCompiler * session = yyextra;
                            session->lineNumberOuter++;
							return SPACE;
						}
{SPACE}                 {
                            return SPACE;
                        }
}

<SC_TAG_CONTROLBLOCK_CONTENT>{
"<"{SPACE}"tree"	                                {
                                                        BEGIN(SC_TREE_PROPERTIES);
                                                        return TAG_TREE_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"tree"{SPACE}">"	    {
                                                        return TAG_TREE_BLOCK_CLOSE;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"controlblock"{SPACE}">"	{
                                                            BEGIN(INITIAL);
                                                            return TAG_CONTROLBLOCK_CLOSE;
                                                        }
{SPACE}\n{SPACE}									{
														SodiumCompiler *session = yyextra;
                                                        session->lineNumberOuter++;
														return SPACE;
													}
{SPACE}                                             {
                                                        return SPACE;
                                                    }
.                                                   {
                                                        return HTMLTEXT;
                                                    }
}

 /* ############################################################################################
    HT/SQL Data Block
    ############################################################################################
 */
"<"{SPACE}"datablock"	{
                            BEGIN(SC_DATABLOCK_PROPERTIES);
                            return TAG_DATABLOCK_OPEN;
                        }


<SC_DATABLOCK_PROPERTIES>{
"connection\-name"      {
                            return PROP_BLOCK_CONNECTION_NAME;
                        }
"auto-generated-columns" {
							return PROP_BLOCK_AUTO_GENERATED_COLUMNS;
						}
"join-condition"        {
                            return PROP_BLOCK_JOIN_CONDITION;
                        }
"record\-count"         {
                            return PROP_BLOCK_RECORD_COUNT;
                        }
"data\-source\-name"    {
                            return PROP_BLOCK_DATA_SOURCE_NAME;
                        }
"data\-schema\-name"    {
							return PROP_BLOCK_DATA_SCHEMA_NAME;
						}
"data\-block\-name"     {
                            return PROP_BLOCK_BLOCK_NAME;
                        }
"key\-column\-name"     {
                            return PROP_BLOCK_KEY_COLUMN_NAME;
                        }
"master\-data\-block\-name"     {
                                    return PROP_BLOCK_MASTER_BLOCK_NAME;
                                }
"insert\-allowed"       {
                            return PROP_BLOCK_INSERT_ALLOWED;
                        }
"delete\-allowed"       {
                            return PROP_BLOCK_DELETE_ALLOWED;
                        }
"update\-allowed"       {
                            return PROP_BLOCK_UPDATE_ALLOWED;
                        }
"where\-clause"         {
                            return PROP_BLOCK_WHERE_CLAUSE;
                        }
"order\-by\-clause"     {
                            return PROP_BLOCK_OREDERBY_CLAUSE;
                        }
[a-zA-Z_]([^\n\t <>=?;"'\(\)\[\]\{\}])*	    {
												return PROPERTYID;
											}
{SPACE}"="{SPACE}		{
                            return ASSIGMENT;
                        }
\"([^\"])*\"	        {
                            return PROPERTYDATA;
                        }
">"				        {
							BEGIN(SC_TAG_DATABLOCK_CONTENT);
                            return TAG_CLOSE;
						}
{SPACE}\n{SPACE}		{
							SodiumCompiler * session = yyextra;
                            session->lineNumberOuter++;
							return SPACE;
						}
{SPACE}                 {
                            return SPACE;
                        }

}






 /* ############################################################################################
    HT/SQL Table
    ############################################################################################
 */
<SC_TAG_DATABLOCK_CONTENT>{
"<"{SPACE}"table"	                                {
                                                        BEGIN(SC_HTSQL_TAGPROPERTY);
                                                        return TAG_TABLE_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"table"{SPACE}">"	{
														//BEGIN(INITIAL);
														return TAG_TABLE_BLOCK_CLOSE;
													}
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"datablock"{SPACE}">"	{
                                                            BEGIN(INITIAL);
                                                            return TAG_DATABLOCK_BLOCK_CLOSE;
                                                        }
"<"{SPACE}"thead"									{
                                                        BEGIN(SC_HTSQL_TAGPROPERTY);
                                                        return TAG_THEAD_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"thead"{SPACE}">"	{
														return TAG_THEAD_BLOCK_CLOSE;
													}
"<"{SPACE}"tfoot"	                                {
                                                        BEGIN(SC_HTSQL_TAGPROPERTY);
                                                        return TAG_TFOOT_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"tfoot"{SPACE}">"	{
														return TAG_TFOOT_BLOCK_CLOSE;
													}
"<"{SPACE}"tbody"	                                {
                                                        BEGIN(SC_HTSQL_TAGPROPERTY);
                                                        return TAG_TBODY_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"tbody"{SPACE}">"	{
														return TAG_TBODY_BLOCK_CLOSE;
													}
"<"{SPACE}"tr"		                                {
                                                        BEGIN(SC_HTSQL_TAGPROPERTY);
                                                        return TAG_TR_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"tr"{SPACE}">"	    {
                                                        return TAG_TR_BLOCK_CLOSE;
                                                    }
"<"{SPACE}"td"                                      {
                                                        BEGIN(SC_HTSQL_TAGPROPERTY);
                                                        return TAG_TD_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"td"{SPACE}">"	    {
                                                        return TAG_TD_BLOCK_CLOSE;
                                                    }
"<"{SPACE}"th"                                      {
                                                        BEGIN(SC_HTSQL_TAGPROPERTY);
                                                        return TAG_TH_OPEN;
                                                    }
"<"{SPACE}{TAGCLOSECHAR}{SPACE}"th"{SPACE}">"	    {
                                                        return TAG_TH_BLOCK_CLOSE;
                                                    }
 /* ############################################################################################
    HT/SQL Input & Select
    ############################################################################################
 */
"<"{SPACE}"input"	    {
                            BEGIN(SC_INPUT_PROPERTIES);
                            return TAG_INPUT_OPEN;
                        }
"<"{SPACE}"textarea"	{
                            BEGIN(SC_INPUT_PROPERTIES);
                            return TAG_TEXTAREA_OPEN;
                        }
"<"{SPACE}"select"	    {
                            BEGIN(SC_INPUT_PROPERTIES);
                            return TAG_SELECT_OPEN;
                        }
{SPACE}"<"{SPACE}{TAGCLOSECHAR}{SPACE}"input"{SPACE}">"		{
																return TAG_INPUT_BLOCK_CLOSE;
															}
{SPACE}"<"{SPACE}{TAGCLOSECHAR}{SPACE}"textarea"{SPACE}">"	{
																return TAG_TEXTAREA_BLOCK_CLOSE;
															}
{SPACE}"<"{SPACE}{TAGCLOSECHAR}{SPACE}"select"{SPACE}">"	{
																return TAG_SELECT_BLOCK_CLOSE;
															}
\n{SPACE}											{
														SodiumCompiler * session = yyextra;
                                                        session->lineNumberOuter++;
													}
{SPACE}                                             {
                                                        return SPACE;
                                                    }
.                                                   {
                                                        return HTMLTEXT;
                                                    }
}


 /* ############################################################################################
    SC_HTSQL_TAGPROPERTY
    ############################################################################################
 */
<SC_HTSQL_TAGPROPERTY>{
[a-zA-Z_]([^\n\t <>=?;"'\(\)\[\]\{\}])*				{
														return PROPERTYID;
													}
{SPACE}"="{SPACE}   		                        {
                                                        return ASSIGMENT;
                                                    }
\"([^\"])*\"	                                    {
                                                        return PROPERTYDATA;
                                                    }
{SPACE}                                             {
                                                        return SPACE;
                                                    }
">"						                            {
                                                      BEGIN(SC_TAG_DATABLOCK_CONTENT);
                                                      return TAG_CLOSE;
                                                    }
}


<SC_INPUT_PROPERTIES>{
"name"                      {
                                return PROP_INPUT_NAME;
                            }
"master\-item\-name"        {
                                return PROP_INPUT_MASTER_ITEM_NAME;
                            }
"column\-name"              {
                                return PROP_INPUT_COLUMN_NAME;
                            }
"sequence\-name"            {
                                return PROP_INPUT_SEQUENCE_NAME;
                            }
"sequence\-schema\-name"    {
                                return PROP_INPUT_SEQUENCE_SCHEMA_NAME;
                            }
"type"                      {
                                return PROP_INPUT_TYPE;
                            }
"value"                     {
                                return PROP_INPUT_VALUE;
                            }
"default\-value"            {
                                return PROP_INPUT_DEFAULT_VALUE;
                            }
"checked\-value"            {
                                return PROP_INPUT_CHECKED_VALUE;
                            }
"unchecked\-value"          {
                                return PROP_INPUT_UNCHECKED_VALUE;
                            }
"format\-mask"              {
                                return PROP_INPUT_FORMAT_MASK;
                            }
"data\-type"                {
                                return PROP_INPUT_DATA_TYPE;
                            }
"maxlength"                 {
                                return PROP_INPUT_MAX_LENGTH;
                            }
"insert\-allowed"           {
                                return PROP_INPUT_INSERT_ALLOWED;
                            }
"update\-allowed"           {
                                return PROP_INPUT_UPDATE_ALLOWED;
                            }
"datalist-name"             {
                                return PROP_INPUT_DATALIST_NAME;
                            }
"lookup-input-name"			{
                                return PROP_INPUT_LOOKUP_ITEM_NAME;
                            }
"lookup-input-block-name"	{
								return PROP_INPUT_LOOKUP_ITEM_BLOCK_NAME;
							}
[a-zA-Z_]([^\n\t <>=?;"'\(\)\[\]\{\}])*	    {
												return PROPERTYID;
											}
{SPACE}"="{SPACE}         			        {
                                                return ASSIGMENT;
                                            }
\"([^\"])*\"	                            {
                                                return PROPERTYDATA;
                                            }
{SPACE}"/"{SPACE}">"{SPACE}					{
												BEGIN(SC_TAG_DATABLOCK_CONTENT);
												return TAG_SHORT_CLOSE;
											}
">"				                            {
                                                BEGIN(SC_TAG_DATABLOCK_CONTENT);
                                                return TAG_CLOSE;
                                            }
\n											{
												SodiumCompiler * session = yyextra;
												session->lineNumberOuter++;
											}
{SPACE}                                     {
                                                return SPACE;
                                            }
}


%%

