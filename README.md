# CY-Fighters

A turn-based fighting game implemented in C for the terminal. Developed as part of the préING1 curriculum at CY Tech (2024-2025). Players assemble teams of fighters and battle against another player or the CPU, utilizing unique stats and special techniques loaded from external files.
## Description

CY-Fighters is a command-line based game where two teams of fighters clash in turn-based combat. The core focus of the project is on data management through files, C structures, and creating an ergonomic user interface within the limitations of a standard terminal.

Each fighter possesses distinct characteristics (HP, Attack, Defense, Agility, Speed) and can use both basic attacks and unique special techniques. The turn order is determined by fighter speed, and combat continues until all fighters on one team are knocked out (HP <= 0).

## Features

*   **Team-Based Combat:** Assemble a team of fighters to battle another team.
*   **Turn-Based System:** Actions are taken sequentially based on fighter speed.
*   **Character Stats:** Fighters have unique stats influencing their performance (HP, Max HP, Attack, Defense, Agility, Speed).
*   **Special Techniques:** Fighters can use powerful special moves with various effects (damage, buffs, debuffs), durations, and cooldowns.
*   **Data-Driven:** Fighter stats and special techniques are defined and loaded from external text files, allowing for easy modification and expansion.
*   **Text-Based Interface:** All gameplay occurs within the terminal, designed for clarity and usability.
*   **1v1 or 1vCPU:** Play against another human player or challenge the computer AI (with potential difficulty levels).
*   **Temporary Effects:** Special techniques can apply temporary status effects (positive or negative) to fighters.

## Interface Preview

The game interface is rendered entirely in the terminal. It aims to clearly display:
*   Both teams with their fighters.
*   Current HP / Max HP for each fighter (potentially as a bar).
*   Indicators for active status effects.
*   Whose turn it is.
*   Available actions (Attack, Techniques).
*   Prompts for selecting actions and targets.
