/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 * Copyright (C) 2010 - 2013 Eluna Lua Engine <http://emudevs.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "LuaEngine.h"
#include "GameObjectMethods.h"

int LuaGameObject::GetMap(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetMap());
    return 1;
}


int LuaGameObject::GetRelativePoint(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    float dist = luaL_checknumber(L, 1);
    int deg = luaL_checkinteger(L, 2);

    float o = MapManager::NormalizeOrientation(go->GetOrientation() + (deg*M_PI / 180));
    sEluna.Push(L, go->GetPositionX() + (dist*cosf(o)));
    sEluna.Push(L, go->GetPositionY() + (dist*sinf(o)));
    sEluna.Push(L, o);
    return 3;
}


int LuaGameObject::GetGUID(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetGUIDLow());
    return 1;
}


int LuaGameObject::CastSpell(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint32 spell = luaL_checkunsigned(L, 1);
    Unit* target = sEluna.CHECK_UNIT(L, 2);
    /*if (target)
        go->CastSpell(target, spell);*/
    return 0;
}


int LuaGameObject::GetX(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetPositionX());
    return 1;
}


int LuaGameObject::GetY(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetPositionY());
    return 1;
}


int LuaGameObject::GetZ(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetPositionZ());
    return 1;
}

int LuaGameObject::GetO(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetOrientation());
    return 1;
}

int LuaGameObject::GetLocation(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetPositionX());
    sEluna.Push(L, go->GetPositionY());
    sEluna.Push(L, go->GetPositionZ());
    sEluna.Push(L, go->GetOrientation());
    return 4;
}

int LuaGameObject::GetMapId(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetMapId());
    return 1;
}

int LuaGameObject::GetZoneId(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetZoneId());
    return 1;
}


int LuaGameObject::GetAreaId(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetAreaId());
    return 1;
}


int LuaGameObject::GetName(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetName());
    return 1;
}

int LuaGameObject::GetEntry(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetEntry());
    return 1;
}

int LuaGameObject::SummonCreature(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint32 entry = luaL_checkunsigned(L, 1);
    float x = luaL_checknumber(L, 2);
    float y = luaL_checknumber(L, 3);
    float z = luaL_checknumber(L, 4);
    float o = luaL_checknumber(L, 5);
    uint32 spawnType = luaL_optunsigned(L, 6, 0);
    uint32 despawnTimer = luaL_optunsigned(L, 7, 0);

    TempSummonType type;
    switch (spawnType)
    {
        case 1:
            type = TEMPSUMMON_TIMED_OR_DEAD_DESPAWN;
            break;
        case 2:
            type = TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN;
            break;
        case 3:
            type = TEMPSUMMON_TIMED_DESPAWN;
            break;
        case 4:
            // type = TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT;
            break;
        case 5:
            type = TEMPSUMMON_CORPSE_DESPAWN;
            break;
        case 6:
            type = TEMPSUMMON_CORPSE_TIMED_DESPAWN;
            break;
        case 7:
            type = TEMPSUMMON_DEAD_DESPAWN;
            break;
        case 8:
            type = TEMPSUMMON_MANUAL_DESPAWN;
            break;
    }
    sEluna.Push(L, go->SummonCreature(entry, x, y, z, o, type, despawnTimer));
    return 1;
}

int LuaGameObject::SummonGameObject(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint32 entry = luaL_checkunsigned(L, 1);
    float x = luaL_checknumber(L, 2);
    float y = luaL_checknumber(L, 3);
    float z = luaL_checknumber(L, 4);
    float o = luaL_checknumber(L, 5);
    uint32 respawnDelay = luaL_optunsigned(L, 6, 30);
    sEluna.Push(L, go->SummonGameObject(entry, x, y, z, o, respawnDelay));
    return 1;
}

int LuaGameObject::GetDisplayId(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetDisplayId());
    return 1;
}

int LuaGameObject::GetScale(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetObjectScale());
    return 1;
}

int LuaGameObject::IsInWorld(lua_State* L, GameObject* go)
{
    if (!go)
        sEluna.Push(L, false);
    else
        sEluna.Push(L, go->IsInWorld());
    return 1;
}

int LuaGameObject::HasQuest(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        sEluna.Push(L, false);
    else
    {
        uint32 questId = luaL_checkunsigned(L, 1);
        sEluna.Push(L, go->HasQuest(questId));
    }
    return 1;
}

int LuaGameObject::IsSpawned(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        sEluna.Push(L, false);
    else
        sEluna.Push(L, go->isSpawned());
    return 1;
}

int LuaGameObject::IsTransport(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        sEluna.Push(L, false);
    else
        sEluna.Push(L, go->IsTransport());
    return 1;
}

int LuaGameObject::IsDestructible(lua_State* L, GameObject* go) // TODO: Implementation core side
{
    /*if (!go || !go->IsInWorld())
        sEluna.Push(L, false);
    else
        sEluna.Push(L, go->IsDestructibleBuilding());
    return 1;*/
    return 0; // temp return 0
}

int LuaGameObject::IsActive(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        sEluna.Push(L, false);
    else
        sEluna.Push(L, go->isActiveObject());
    return 1;
}

int LuaGameObject::Move(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    float x = luaL_checknumber(L, 1);
    float y = luaL_checknumber(L, 2);
    float z = luaL_checknumber(L, 3);
    float o = luaL_checknumber(L, 4);
    go->Relocate(x, y, z, o);
    return 0;
}

int LuaGameObject::SaveToDB(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    go->SaveToDB();
    return 0;
}

int LuaGameObject::RemoveFromWorld(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    bool del = luaL_optbool(L, 1, false);
    if (del)
        go->DeleteFromDB();
    go->RemoveFromWorld();
    return 0;
}

int LuaGameObject::SetScale(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    float scale = luaL_checknumber(L, 1);
    go->SetObjectScale(scale);
    return 0;
}

int LuaGameObject::RegisterEvent(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    luaL_checktype(L, 1, LUA_TFUNCTION);
    uint32 delay = luaL_checkunsigned(L, 2);
    uint32 repeats = luaL_checkunsigned(L, 3);

    lua_settop(L, 1);
    Eluna::LuaEventMap* eventMap = Eluna::LuaEventMap::GetEvents(go);
    if (!eventMap)
    {
        luaL_error(L, "You need to use RegisterGameObjectEvent for the gameobject first");
        return 0;
    }

    int functionRef = lua_ref(L, true);
    eventMap->ScriptEventCreate(functionRef, delay, repeats);
    sEluna.Push(L, functionRef);
    return 1;
}

int LuaGameObject::RemoveEventById(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    int eventID = luaL_checkinteger(L, 1);
    Eluna::LuaEventMap* eventMap = Eluna::LuaEventMap::GetEvents(go);
    if (eventMap)
        eventMap->ScriptEventCancel(eventID);
    return 0;
}

int LuaGameObject::RemoveEvents(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    Eluna::LuaEventMap* eventMap = Eluna::LuaEventMap::GetEvents(go);
    if (eventMap)
        eventMap->ScriptEventsReset();
    return 0;
}

int LuaGameObject::GetInt32Value(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint16 index = luaL_checkunsigned(L, 1);
    sEluna.Push(L, go->GetInt32Value(index));
    return 1;
}

int LuaGameObject::GetUInt32Value(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint16 index = luaL_checkunsigned(L, 1);
    sEluna.Push(L, go->GetUInt32Value(index));
    return 1;
}

int LuaGameObject::GetFloatValue(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint16 index = luaL_checkunsigned(L, 1);
    sEluna.Push(L, go->GetFloatValue(index));
    return 1;
}

int LuaGameObject::GetByteValue(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint16 index = luaL_checkunsigned(L, 1);
    uint8 offset = luaL_checkunsigned(L, 2);
    sEluna.Push(L, go->GetByteValue(index, offset));
    return 1;
}

int LuaGameObject::GetUInt16Value(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint16 index = luaL_checkunsigned(L, 1);
    uint8 offset = luaL_checkunsigned(L, 2);
    sEluna.Push(L, go->GetUInt16Value(index, offset));
    return 1;
}

int LuaGameObject::SetInt32Value(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint16 index = luaL_checkunsigned(L, 1);
    int32 value = luaL_checkinteger(L, 2);
    go->SetInt32Value(index, value);
    return 0;
}

int LuaGameObject::SetUInt32Value(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint16 index = luaL_checkunsigned(L, 1);
    uint32 value = luaL_checkunsigned(L, 2);
    go->SetUInt32Value(index, value);
    return 0;
}

int LuaGameObject::UpdateUInt32Value(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint16 index = luaL_checkunsigned(L, 1);
    uint32 value = luaL_checkunsigned(L, 2);
    go->UpdateUInt32Value(index, value);
    return 0;
}

int LuaGameObject::SetFloatValue(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint16 index = luaL_checkunsigned(L, 1);
    float value = luaL_checknumber(L, 2);
    go->SetFloatValue(index, value);
    return 0;
}

int LuaGameObject::SetByteValue(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint16 index = luaL_checkunsigned(L, 1);
    uint8 offset = luaL_checkunsigned(L, 2);
    uint8 value = luaL_checkunsigned(L, 3);
    go->SetByteValue(index, offset, value);
    return 0;
}

int LuaGameObject::SetUInt16Value(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint16 index = luaL_checkunsigned(L, 1);
    uint8 offset = luaL_checkunsigned(L, 2);
    uint16 value = luaL_checkunsigned(L, 3);
    go->SetUInt16Value(index, offset, value);
    return 0;
}

int LuaGameObject::SetInt16Value(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint16 index = luaL_checkunsigned(L, 1);
    uint8 offset = luaL_checkunsigned(L, 2);
    int16 value = luaL_checkinteger(L, 3);
    go->SetInt16Value(index, offset, value);
    return 0;
}

int LuaGameObject::GetGUIDLow(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetGUIDLow());
    return 1;
}

int LuaGameObject::GetNearestPlayer(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    float distance = luaL_optnumber(L, 1, SIZE_OF_GRIDS);

    Player* target = NULL;
    Eluna::NearestTypeWithEntryInRangeCheck checker(go, distance, TYPEID_PLAYER);
    // MaNGOS::PlayerLastSearcher<Eluna::NearestTypeWithEntryInRangeCheck> searcher(go, target, checker);
    // go->VisitNearbyObject(distance, searcher);

    sEluna.Push(L, target);
    return 1;
}

int LuaGameObject::GetNearestGameObject(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint32 entry = luaL_optunsigned(L, 1, 0);
    float range = luaL_optnumber(L, 2, SIZE_OF_GRIDS);

    GameObject* target = NULL;
    Eluna::NearestTypeWithEntryInRangeCheck checker(go, range, TYPEID_GAMEOBJECT, entry);
    // MaNGOS::GameObjectLastSearcher<Eluna::NearestTypeWithEntryInRangeCheck> searcher(go, target, checker);
    // go->VisitNearbyGridObject(range, searcher);

    sEluna.Push(L, target);
    return 1;
}

int LuaGameObject::GetNearestCreature(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint32 entry = luaL_optunsigned(L, 1, 0);
    float range = luaL_optnumber(L, 2, SIZE_OF_GRIDS);

    Creature* target = NULL;
    Eluna::NearestTypeWithEntryInRangeCheck checker(go, range, TYPEID_UNIT, entry);
    // MaNGOS::CreatureLastSearcher<Eluna::NearestTypeWithEntryInRangeCheck> searcher(go, target, checker);
    // go->VisitNearbyGridObject(range, searcher);

    sEluna.Push(L, target);
    return 1;
}

int LuaGameObject::UseDoorOrButton(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint32 delay = luaL_optunsigned(L, 1, 0);

    go->UseDoorOrButton(delay);
    return 0;
}

int LuaGameObject::SetGoState(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint32 state = luaL_optunsigned(L, 1, 0);

    if (state == 0)
        go->SetGoState(GO_STATE_ACTIVE);
    else if (state == 1)
        go->SetGoState(GO_STATE_READY);
    else if (state == 2)
        go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);

    return 0;
}

int LuaGameObject::GetGoState(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->GetGoState());
    return 1;
}

int LuaGameObject::SetLootState(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint32 state = luaL_optunsigned(L, 1, 0);

    if (state == 0)
        go->SetLootState(GO_NOT_READY);
    else if (state == 1)
        go->SetLootState(GO_READY);
    else if (state == 2)
        go->SetLootState(GO_ACTIVATED);
    else if (state == 3)
        go->SetLootState(GO_JUST_DEACTIVATED);

    return 0;
}

int LuaGameObject::GetLootState(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    sEluna.Push(L, go->getLootState());
    return 1;
}

int LuaGameObject::SetFlag(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint32 flag = luaL_optunsigned(L, 1, 0);

    go->SetFlag(GAMEOBJECT_FLAGS, flag);
    return 0;
}

int LuaGameObject::RemoveFlag(lua_State* L, GameObject* go)
{
    if (!go || !go->IsInWorld())
        return 0;

    uint32 flag = luaL_optunsigned(L, 1, 0);

    go->RemoveFlag(GAMEOBJECT_FLAGS, flag);
    return 0;
}

int LuaGameObject::Despawn(lua_State* L, GameObject* go)
{
    if (!go)
        return 0;

    int32 delay = luaL_optint(L, 1, 1);

    if (delay <= 0)
        delay = 1;
    // go->SetSpawnedByDefault(false);
    go->SetRespawnTime(delay);
    return 0;
}

int LuaGameObject::Respawn(lua_State* L, GameObject* go)
{
    if (!go)
        return 0;

    int32 delay = luaL_optint(L, 1, 1);

    if (delay <= 0)
        delay = 1;
    // go->SetSpawnedByDefault(true);
    go->SetRespawnTime(delay);
    return 0;
}