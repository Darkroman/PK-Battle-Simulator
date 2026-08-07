#pragma once

#include "interfaces/IBattleAnnouncerUI.h"

struct BattleContext;

class BattleAnnouncerHeadless : public IBattleAnnouncerUI
{
public:
    void ThrowOutFirstPokemon(const BattleContext&) const override {}
    void DisplayFightingPokemon(const BattleContext&) const override {}
    bool AnnounceWinner(const BattleContext& context) override { return false; }

    void NewLine() const override {}
    void DisplayTurnNumber(int) const override {}
};