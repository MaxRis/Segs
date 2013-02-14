/*
 * Super Entity Game Server
 * http://segs.sf.net/
 * Copyright (c) 2006 Super Entity Game Server Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 *
 */

#include "Opcodes.h"
#include "NameTables.h"

NameTableEntry OpcodeNames[] =
{
    { COMM_CONTROLCOMMAND,      "COMM_CONTROLCOMMAND" },
    { COMM_CONNECT,             "COMM_CONNECT" },
    { SERVER_UPDATE,            "SERVER_UPDATE" },
    { SERVER_ALLENTS,           "SERVER_ALLENTS" },
    { SERVER_CMDSHORTCUTS,      "SERVER_CMDSHORTCUTS" },
    { SERVER_CONNECT_MSG,       "SERVER_CONNECT_MSG" },
    { SERVER_GROUPS,            "SERVER_GROUPS" },
    { SERVER_EDITMSG,           "SERVER_EDITMSG" },
    { SERVER_DEBUGCMD,          "SERVER_DEBUGCMD" },
    { SERVER_SENDENTDEBUGMENU,  "SERVER_SENDENTDEBUGMENU" },
    { SERVER_MAPXFERWAIT,       "SERVER_MAPXFERWAIT" },
    { SERVER_MAPXFER,           "SERVER_MAPXFER" },
    { SERVER_FORCE_LOGOUT,      "SERVER_FORCE_LOGUT" },
    { SERVER_GAME_CMDS,         "SERVER_GAME_CMDS" },
    { SERVER_RECEIVE_DIALOG,    "SERVER_RECEIVE_DIALOG" },
    { SERVER_RECEIVE_DIALOG_POWREQ, "SERVER_RECIEVE_DIALOG_POWREQ" },
    { SERVER_RECEIVE_DIALOG_NAG,	   "SERVER_RECIEVE_DIALOG_NAG" },
    { SERVER_RECEIVE_INFO_BOX,	   "SERVER_RECIEVE_INFO_BOX" },
    { SERVER_DOOR_CMD,			   "SERVER_DOOR_CMD" },
    { SERVER_SEND_CONSOLE_OUTPUT,   "SERVER_SEND_CONSOLE_OUTPUT" },
    { SERVER_SET_CLIENT_STATE,	   "SERVER_SET_CLIENT_STATE" },
    { SERVER_CON_PRINTF,			   "SERVER_CON_PRINTF" },
    { SERVER_SEND_CHAT_MSG,	   "SERVER_SEND_CHAT_MSG" },
    { SERVER_SEND_FLOATING_DAMAGE,  "SERVER_SEND_FLOATING_DAMAGE" },
    { SERVER_VISITED_MAP_CELLS,	   "SERVER_VISITED_MAP_CELLS" },
    { SERVER_UPDATE_WAYPOINT,	   "SERVER_UPDATE_WAYPOINT" },
    { SERVER_SET_WAYPOINT,	       "SERVER_SET_WAYPOINT" },
    { SERVER_TEAM_OFFER,			   "SERVER_TEAM_OFFER" },
    { SERVER_TASKFORCE_KICK,		   "SERVER_TASKFORCE_KICK" },
    { SERVER_TASKFORCE_QUIT,		   "SERVER_TASKFORCE_QUIT" },
    { SERVER_SIDEKICK_OFFER,		   "SERVER_SIDEKICK_OFFER" },
    { SERVER_SUPERGROUP_OFFER,	   "SERVER_SUPERGROUP_OFFER" },
    { SERVER_SGROUP_CREATE_REPLY,   "SERVER_SGROUP_CREATE_REPLY" },
    { SERVER_SUPERGROUP_COSTUME,	   "SERVER_SUPERGROUP_COSTUME" },
    { SERVER_ALLIANCE_OFFER,		   "SERVER_ALLIANCE_OFFER" },
    { SERVER_CUTSCENE_UPDATE,	   "SERVER_CUTSCENE_UPDATE" },
    { SERVER_TRADE_OFFER,		   "SERVER_TRADE_OFFER" },
    { SERVER_TRADE_INIT,			   "SERVER_TRADE_INIT" },
    { SERVER_TRADE_CANCEL,		   "SERVER_TRADE_CANCEL" },
    { SERVER_TRADE_UPDATE,		   "SERVER_TRADE_UPDATE" },
    { SERVER_TRADE_SUCCESS,		   "SERVER_TRADE_SUCCESS" },
    { SERVER_SEND_FRIENDS,	   "SERVER_SEND_FRIENDS" },
    { SERVER_CONTROL_PLAYER,		   "SERVER_CONTROL_PLAYER" },
    { SERVER_CONTACT_DIALOG_OPEN,   "SERVER_CONTACT_DIALOG_OPEN" },
    { SERVER_CONTACT_DIALOG_CLOSE,  "SERVER_CONTACT_DIALOG_CLOSE" },
    { SERVER_CONTACT_DIALOG_OK,	   "SERVER_CONTACT_DIALOG_OK" },
    { SERVER_CONTACT_DIALOG_YESNO,  "SERVER_CONTACT_DIALOG_YESNO" },
    { SERVER_CONTACT_STATUS,		   "SERVER_CONTACT_STATUS" },
    { SERVER_CONTACT_SELECT,		   "SERVER_CONTACT_SELECT" },
    { SERVER_TASK_STATUS,		   "SERVER_TASK_STATUS" },
    { SERVER_TASK_SELECT,		   "SERVER_TASK_SELECT" },
    { SERVER_TASKS_REMOVE_TEAMMATE_TASKS, "SERVER_TAKS_REMOVE_TEAMMATE_TASKS" },
    { SERVER_MISSION_ENTRY,		   "SERVER_MISSION_ENTRY" },
    { SERVER_MISSION_KICKTIMER,	   "SERVER_MISSION_KICKTIMER" },
    { SERVER_DEAD_NOGURNEY,		   "SERVER_DEAD_NOGURNEY" },
    { SERVER_DOORANIM,			   "SERVER_DOORANIM" },
    { SERVER_DOOREXIT,			   "SERVER_DOOREXIT" },
    { SERVER_FACE_ENTITY,		   "SERVER_FACE_ENTITY" },
    { SERVER_FACE_LOCATION,		   "SERVER_FACE_LOCATION" },
    { SERVER_SEND_FLOATING_INFO,	   "SERVER_SEND_FLOATING_INFO" },
    { SERVER_SET_STANCE,			   "SERVER_SET_STANCE" },
    { SERVER_MAP_XFER_LIST,		   "SERVER_MAP_XFER_LIST" },
    { SERVER_MAP_XFER_LIST_CLOSE,   "SERVER_MAP_XFER_LIST_CLOSE" },
    { SERVER_ENABLE_CONTROL_LOG,	   "SERVER_ENABLE_CONTROL_LOG" },
    { SERVER_LEVEL_UP,			   "SERVER_LEVEL_UP" },
    { SERVER_UNLOCK_SKILLS,		   "SEVER_UNLOCK_SKILLS" },
    { SERVER_NEW_TITLE,			   "SERVER_NEW_TITLE" },
    { SERVER_PERFORMANCE_UPDATE,	   "SERVER_PERFORMANCE_UPDATE" },
    { SERVER_CSR_BUG_REPORT,	   "SERVER_CSR_BUG_REPORT" },
    { SERVER_SEND_EMAIL_HEADERS,	   "SERVER_SEND_EMAIL_HEADERS" },
    { SERVER_SEND_EMAIL_MESSAGE,  "SERVER_SEND_EMAIL_MESSAGE" },
    { SERVER_SEND_EMAIL_MESSAGE_STATUS, "SERVER_SEND_EMAIL_MESSAGE_STATUS" },
    { SERVER_TASK_VISITLOCATION_UPDATE, "SERVER_TASK_VISITLOCATION_UPDATE" },
    { SERVER_SEND_PLAYER_INFO,		   "SERVER_SEND_PLAYER_INFO" },
    { SERVER_CLUE_UPDATE,			   "SERVER_CLUE_UPDATE" },
    { SERVER_KEYCLUE_UPDATE,		   "SERVER_KEYCLUE_UPDATE" },
    { SERVER_SOUVENIRCLUE_UPDATE,	   "SERVER_SOUVENIRCLUE_UPDATE" },
    { SERVER_SOUVENIRCLUE_DETAIL,	   "SERVER_SOUVENIRCLUE_DETAIL" },
    { SERVER_MISSION_OBJECTIVE_TIMER_UPDATE, "SRVER_MISSION_OBJECTIVE_TIMER_UPDATE" },
    { SERVER_REGISTER_SUPERGROUP,       "SERVER_REGISTER_SUPERGROUP" },
    { SERVER_SUPERGROUP_LIST,		   "SERVER_SUPERGROUP_LIST" },
    { SERVER_SGRAID_LIST,			   "SERVER_SGRAID_LIST" },
    { SERVER_TASK_DETAIL,			   "SERVER_TASK_DETAIL" },
    { SERVER_BROWSER_TEXT,			   "SERVER_BROWSER_TEXT" },
    { SERVER_BROWSER_CLOSE,			   "SERVER_BROWSER_CLOSE" },
    { SERVER_STORE_OPEN,		   "SERVER_STORE_OPEN" },
    { SERVER_STORE_CLOSE,			   "SERVER_STORE_CLOSE" },
    { SERVER_BUG_REPORT,			   "SERVER_BUG_REPORT" },
    { SERVER_MISSION_SURVEY,			   "SERVER_MISSION_SURVEY" },
    { SERVER_SEND_TRAY_ADD,			   "SERVER_SEND_TRAY_ADD" },
    { SERVER_COMBINE_RESPONSE,		   "SERVER_COMBINE_RESPONSE" },
    { SERVER_ARENA_KIOSK,			   "SERVER_ARENA_KIOSK" },
    { SERVER_ARENA_EVENTS,			   "SERVER_ARENA_EVENTS" },
    { SERVER_ARENA_EVENTUPDATE,		   "SERVER_ARENA_ENEVTUPDATE" },
    { SERVER_ARENA_UPDATE_TRAY_DISABLE, "SERVER_ARENA_UPDATE_TRAY_DISABLE" },
    { SERVER_ARENAKIOSK_SETOPEN,		   "SERVER_ARENAKISK_SETOPEN" },
    { SERVER_ARENA_OFFER,			   "SERVER_ARENA_OFFER" },
    { SERVER_ARENA_ERROR,			   "SERVER_ARENA_ERROR" },
    { SERVER_SGRAID_COMPASS_STRING,	   "SERVER_SGRAID_COMPASS_STRING" },
    { SERVER_TAILOR_OPEN,			   "SERVER_TAILOR_OPEN" },
    { SERVER_RESPEC_OPEN,			   "SERVER_RESPEC_OPEN" },
    { SERVER_SEARCH_RESULTS,			   "SERVER_SEARCH_RESULTS" },
    { SERVER_VALIDATE_RESPEC,		   "SERVER_VALIDATE_RESPEC" },
    { SERVER_SEND_REWARD_CHOICE,		   "SERVER_SEND_REWARD_CHOICE" },
    { SERVER_LARGE_PACKET,			   "SERVER_LARGE_PACKET" },
    { SERVER_SCRIPT_DEBUGINFO,		   "SERVER_SCRIPT_DEBUGINFO" },
    { SERVER_SHARDCOMM,				   "SERVER_SHARDCOMM" },
    { SERVER_ARENA_UPDATE_PLAYER,	   "SERVER_ARENA_UPDATE_PLAYER" },
    { SERVER_ARENA_REQRESULTS,		   "SERVER_ARENA_REQRESULTS" },
    { SERVER_ARENA_START_COUNT,		   "SERVER_ARENA_START_COUNT" },
    { SERVER_ARENA_COMPASS_STRING,	   "SERVER_ARENA_COMPASS_STRING" },
    { SERVER_ARENA_STOCK_LIVES,		   "SERVER_ARENA_STOCK_LIVES" },
    { SERVER_ARENA_SCHEDULED_TELEPORT,  "SERVER_ARENA_SCHEDULED_TELEPORT" },
    { SERVER_ARENA_RUN_EVENT_WINDOW,	   "SERVER_ARENA_RUN_EVENT_WINDOW" },
    { SERVER_SCRIPT_UI,				   "SERVER_SCRIPT_UI" },
    { SERVER_SCRIPT_UI_UPDATE,		   "SERVER_SCRIPT_UI_UPDATE" },
    { SERVER_ARENA_MANAGEPETS,	  "SERVER_ARENA_MANAGEPETS" },
    { SERVER_UPDATE_PET_STATE,	  "SERVER_UPDATE_PET_STATE" },
    { SERVER_BASE_CREATE,		  "SERVER_BASE_CREAT" },
    { SERVER_CMD_COUNT,           "SERVER_CMD_COUNT" },
};
