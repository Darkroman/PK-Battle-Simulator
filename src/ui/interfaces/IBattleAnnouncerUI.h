#pragma once

struct BattleContext;

class IBattleAnnouncerUI
{
public:
    virtual ~IBattleAnnouncerUI() = default;

    virtual void ThrowOutFirstPokemon(const BattleContext&) const = 0;
    virtual void DisplayFightingPokemon(const BattleContext&) const = 0;
    virtual void AnnounceWinner(const BattleContext&) = 0;

    virtual void NewLine() const = 0;
    virtual void DisplayTurnNumber(int) const = 0;

protected:

};