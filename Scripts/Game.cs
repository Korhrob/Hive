using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class Game
{

    public static int PlatformLayer = 1 << 10;
    public static int InteractLayer = 1 << 11;
    public static int ItemLayer = 1 << 12;
    public static float MaxGravity = 9f;
    public static float Gravity = 1f;

    public static int Score = 0;
    public static int Money = 0;
    public static int Difficulty = 1;
    public static float Timer = 0;

    // Upgrades
    public static int MaxLife = 3;
    public static int MaxCarryCapacity = 3;
    // speed
    // jump height
    // double material chance
    // extra money chance
    // extra time

    public static void StartGame() // move to game manager
    {
        Score = 0;
        Money = 0;
        Timer = 0;
        Difficulty = 1;
    }

}
