#pragma once

class PlayerEntity {
    private:
        char _sign;
    
    public: 
        const char& Sign() const;

        PlayerEntity(const char& sign);
        ~PlayerEntity();
};