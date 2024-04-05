using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Customer : MonoBehaviour
{

    public string display_name = "Customer";
    public Request request;
    private Coroutine timer;

    private void OnEnable()
    {
        request = new Request();
        timer = StartCoroutine(LeaveTimer());
    }

    public void DisplayRequest()
    {

        // display speech bubble and the item

    }

    public void FinishTrade()
    {
        Game.Score++;
        Game.Money++; // should depend on material cost and how fast
        StopCoroutine(timer);
        // could display happy emote here
        StartCoroutine(LeaveAnimation());
    }

    private IEnumerator LeaveTimer()
    {
        yield return new WaitForSeconds(30);
        Game.Score -= Game.Difficulty;
        // could display sad emote here
        StartCoroutine(LeaveAnimation());
    }

    private IEnumerator LeaveAnimation()
    {
        yield return null; // replace with fade + walking animation
        Disable();
    }

    private void Disable()
    {
        gameObject.SetActive(false);
        // release to customer pool
    }

}

public class Request
{
    public enum Type
    {
        Sword,
        Shield,
        Bow,
        Staff,
    }
    public Type type;
    public Item.ID material;
    public int material_quantity;

    public Request()
    {
        type = (Type)Random.Range(0, 3);
        material = TypeToMaterial(type);
        material_quantity = Random.Range(1, 3);
    }

    public Item.ID TypeToMaterial(Type equip)
    {
        switch (equip)
        {
            case Type.Sword: return (Item.ID.Ore);
            case Type.Shield: return (Item.ID.Ore);
            case Type.Bow: return (Item.ID.Log);
            case Type.Staff: return (Item.ID.Log);
        }
        return (Item.ID.DragonScale);
    }

}