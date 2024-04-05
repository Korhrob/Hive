using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Inventory
{

    public int[] inventory;

    public Inventory()
    {
        inventory = new int[3];

        inventory[(int)Item.ID.Ore] = 0;
        inventory[(int)Item.ID.Log] = 0;
    }

    public void AddItem(Item.ID type, int quantity)
    {
        inventory[(int)type] += quantity;
        UI.instance.UpdateResourceCount(inventory);
    }

    // number of items carrying
    public int NumItems()
    {
        return (inventory[(int)Item.ID.Ore] + inventory[(int)Item.ID.Log]);
    }

    public void Empty()
    {
        inventory[(int)Item.ID.Ore] = 0;
        inventory[(int)Item.ID.Log] = 0;
        UI.instance.UpdateResourceCount(inventory);
    }

}