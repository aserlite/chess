#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include "Board.hpp"

class IGameRule {
public:
    virtual ~IGameRule() = default;

    // Prevent copying (no need to copy anyway)
    IGameRule(const IGameRule&)            = delete;
    IGameRule& operator=(const IGameRule&) = delete;

    // Delete moving (same)
    IGameRule(IGameRule&&)            = delete;
    IGameRule& operator=(IGameRule&&) = delete;

    virtual bool overrideMove(Board& /*board*/, Position /*from*/, Position /*to*/) { return false; }

    virtual void onTurnStart(Board& /*board*/, PieceColor /*turn*/) {}

    virtual void                      onPieceCaptured(Board& /*board*/, Position /*pos*/) {}
    [[nodiscard]] virtual std::string getRuleName() const  = 0;
    [[nodiscard]] virtual std::string getMathStats() const = 0;
};

struct RuleFactory {
    std::string                                 name;
    bool                                        enabled;
    std::function<std::unique_ptr<IGameRule>()> create;
};

class RuleRegistry {
public:
    static std::vector<RuleFactory>& getFactories()
    {
        static std::vector<RuleFactory> factories;
        return factories;
    }

    template<typename T>
    static void registerRule(const std::string& name)
    {
        getFactories().push_back({name, false, []() { return std::make_unique<T>(); }});
    }
};

#define REGISTER_RULE(Type, Name)                   \
    namespace {                                     \
    struct RuleRegisterer_##Type {                  \
        RuleRegisterer_##Type()                     \
        {                                           \
            RuleRegistry::registerRule<Type>(Name); \
        }                                           \
    } registerer_##Type;                            \
    }
