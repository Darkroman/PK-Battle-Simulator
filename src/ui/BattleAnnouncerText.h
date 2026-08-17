#pragma once

#include "interfaces/IBattleAnnouncerUI.h"

struct BattleContext;

class BattleAnnouncerText : public IBattleAnnouncerUI
{
public:
    void ThrowOutFirstPokemon(const BattleContext&) const override;
    void DisplayFightingPokemon(const BattleContext&) const override;
    void AnnounceWinner(const BattleContext&) override;

    void NewLine() const override;
    void DisplayTurnNumber(int) const override;

protected:

private:

};