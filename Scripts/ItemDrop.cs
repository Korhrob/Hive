using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemDrop : MonoBehaviour
{

    public Item.ID type;
    public int  quantity;
    public int  pickup_delay;

    private Vector3 direction;
    private float speed;

    public void Initialize(Item.ID type, int quantity)
    {
        this.type = type;
        this.quantity = quantity;
        
        pickup_delay = 30;
        direction = new Vector3(Random.Range(-1f, 1f), Random.Range(-1f, 1f), 0);
        speed = Random.Range(1f, 8f);
    }

    public void FixedUpdate()
    {

        if (pickup_delay > 0)
            pickup_delay--;

        RaycastHit2D ray;
        ray =  Physics2D.Raycast(transform.position, Vector3.down, 0.25f, Game.PlatformLayer);
    
        if (ray)
            speed = 0;
        else
            speed *= 0.95f;

        if (speed > 0)
            transform.position += direction * speed * Time.fixedDeltaTime;

    }

}