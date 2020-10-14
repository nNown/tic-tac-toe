#include <player.h>

const char& PlayerEntity::Sign() const { return this->_sign; }
PlayerEntity::PlayerEntity(const char& sign) : _sign(sign) {}
PlayerEntity::~PlayerEntity() {}