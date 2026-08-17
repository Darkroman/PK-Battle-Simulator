#pragma once

#include "interfaces/IBattleAnnouncerUI.h"

struct BattleContext;

class BattleAnnouncerHeadless : public IBattleAnnouncerUI
{
public:
    void ThrowOutFirstPokemon(const BattleContext&) const override {}
    void DisplayFightingPokemon(const BattleContext&) const override {}
    void AnnounceWinner(const BattleContext& context) override {}

    void NewLine() const override {}
    void DisplayTurnNumber(int) const override {}
};