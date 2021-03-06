#pragma once

#include "Entity.h"
#include "Character.h"

class QString;

/*
 * Entity Methods
 */
// Getters
uint32_t    getIdx(const Entity &e);
uint32_t    getDbId(const Entity &e);
uint32_t    getTargetIdx(const Entity &e);
uint32_t    getAssistTargetIdx(const Entity &e);
glm::vec3   getSpeed(const Entity &e);
float       getBackupSpd(const Entity &e);
float       getJumpHeight(const Entity &e);
uint8_t     getUpdateId(const Entity &e);

// Setters
void    setDbId(Entity &e, uint8_t val);
void    setSpeed(Entity &e, float v1, float v2, float v3);
void    setBackupSpd(Entity &e, float val);
void    setJumpHeight(Entity &e, float val);
void    setUpdateID(Entity &e, uint8_t val);
void    setu1(Entity &e, int val);
void    setu2(Entity &e, int val);
void    setu3(Entity &e, int val);
void    setu4(Entity &e, int val);
void    setu5(Entity &e, int val);
void    setu6(Entity &e, int val);

// Toggles
void    toggleFly(Entity &e);
void    toggleFalling(Entity &e);
void    toggleJumping(Entity &e);
void    toggleSliding(Entity &e);
void    toggleStunned(Entity &e);
void    toggleJumppack(Entity &e);
void    toggleControlsDisabled(Entity &e);
void    toggleFullUpdate(Entity &e);
void    toggleControlId(Entity &e);

// Misc Methods
void    charUpdateDB(Entity *e);
int     getEntityOriginIndex(bool is_player,const QString &origin_name);
int     getEntityClassIndex(bool is_player, const QString &class_name);

/*
 * Character Methods
 */
// Getters
uint32_t            getLevel(const Character &c);
uint32_t            getCombatLevel(const Character &c);
uint32_t            getHP(const Character &c);
uint32_t            getEnd(const Character &c);
uint64_t            getLastCostumeId(const Character &c);
const QString &     getOrigin(const Character &c);
const QString &     getClass(const Character &c);
const QString &     getMapName(const Character &c);
uint32_t            getXP(const Character &c);
uint32_t            getDebt(const Character &c);
uint32_t            getPatrolXP(const Character &c);
const QString &     getTitles(const Character &c);
uint32_t            getInf(const Character &c);
const QString &     getDescription(const Character &c);
const QString &     getBattleCry(const Character &c);
const QString &     getAlignment(const Character &c);


// Setters
void    setLevel(Character &c, uint32_t val);
void    setCombatLevel(Character &c, uint32_t val);
void    setHP(Character &c, uint32_t val);
void    setEnd(Character &c, uint32_t val);
void    setLastCostumeId(Character &c, uint64_t val);
void    setMapName(Character &c, const QString &val);
void    setXP(Character &c, uint32_t val);
void    setDebt(Character &c, uint32_t val);
void    setTitles(Character &c, bool prefix = false, QString generic = "", QString origin = "", QString special = "");
void    setInf(Character &c, uint32_t val);
void    setDescription(Character &c, QString val);
void    setBattleCry(Character &c, QString val);

// Toggles
void    toggleAFK(Character &c, const QString &msg = "");
void    toggleLFG(Character &c);
