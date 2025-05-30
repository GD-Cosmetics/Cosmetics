#pragma once

#include <vector>

#include <matjson.hpp>

enum CosmeticType {
    Hat,
    Mask,
    Object,
    ParticleEffect,
    None
};

class Cosmetic {
public:
    Cosmetic() {}

    Cosmetic(int cosmeticID, std::string cosmeticName, int cosmeticAmount, int isActive) {
        this->cosmeticID = cosmeticID;
        this->cosmeticName = cosmeticName;
        this->cosmeticAmount = cosmeticAmount;
        this->isActive = (isActive == 0) ? false : true;
    }

    Cosmetic(matjson::Value value) {
        this->cosmeticID = value["cosmeticID"].asInt().unwrap();
        this->cosmeticName = value["cosmeticName"].asString().unwrap();
        this->cosmeticAmount = value["cosmeticAmount"].asInt().unwrapOr(0);
        this->isActive = (value["isActive"].asInt().unwrapOr(0) == 0) ? false : true;
    }

    int getCosmeticID() {return this->cosmeticID;}
    std::string getCosmeticName() {return this->cosmeticName;}
    int getCosmeticAmount() {return this->cosmeticAmount;}

    bool isEmpty() {
        if (cosmeticID == 0) 
            return true;

        return false;
    }

    CosmeticType typeFromID() {
        if (this->cosmeticID > 1000 && this->cosmeticID < 2000) {
            return CosmeticType::Hat;
        } else if (this->cosmeticID > 2000 && this->cosmeticID < 3000) {
            return CosmeticType::Mask;
        } else if (this->cosmeticID > 3000 && this->cosmeticID < 4000) {
            return CosmeticType::Object;
        } else if (this->cosmeticID > 4000 && this->cosmeticID < 5000) {
            return CosmeticType::ParticleEffect;
        }

        return CosmeticType::None;
    }

    void setCosmeticID(int cosID) {this->cosmeticID = cosID;}
    void setCosmeticName(std::string name) {this->cosmeticName = name;}
    void setCosmeticAmount(int amount) {this->cosmeticAmount = amount;}
protected:
    int cosmeticID = 0;
    std::string cosmeticName;
    int cosmeticAmount = 0;
    bool isActive = false;
    CosmeticType type;
};

class ActiveCosmetics {
public:
    ActiveCosmetics() {}

    ActiveCosmetics(Cosmetic hat, Cosmetic mask, Cosmetic object, Cosmetic particle) :
        hat(hat),
        mask(mask),
        object(object),
        particle(particle) {}

    Cosmetic getHat() { return this->hat; }
    Cosmetic getMask() { return this->mask; }
    Cosmetic getObject() { return this->object; }
    Cosmetic getParticle() { return this->particle; }

    bool isEmpty() {
        if (hat.isEmpty() && mask.isEmpty() && object.isEmpty() && particle.isEmpty()) return true;

        return false;
    }

    void setHat(Cosmetic hat) { this->hat = hat; }
    void setMask(Cosmetic mask) { this->mask = mask; }
    void setObject(Cosmetic object) { this->object = object; }
    void setParticle(Cosmetic particle) { this->particle = particle; }

protected:
    Cosmetic hat;
    Cosmetic mask;
    Cosmetic object;
    Cosmetic particle;
};

class AccountCosmetics {
public:
    AccountCosmetics() {}

    AccountCosmetics(std::vector<Cosmetic> hats, std::vector<Cosmetic> masks, 
        std::vector<Cosmetic> objects, std::vector<Cosmetic> particles) :
        hats(hats),
        masks(masks),
        objects(objects),
        particles(particles) {}
    
    std::vector<Cosmetic> getHats() { return this->hats; }
    std::vector<Cosmetic> getMasks() { return this->masks; }
    std::vector<Cosmetic> getObjects() { return this->objects; }
    std::vector<Cosmetic> getParticles() { return this->particles; }

    void addHat(Cosmetic hat) { this->hats.push_back(hat); }
    void addMask(Cosmetic mask) { this->masks.push_back(mask); }
    void addObject(Cosmetic object) { this->objects.push_back(object); }
    void addParticle(Cosmetic particle) { this->particles.push_back(particle); }

protected:
    std::vector<Cosmetic> hats;
    std::vector<Cosmetic> masks;
    std::vector<Cosmetic> objects;
    std::vector<Cosmetic> particles;
};