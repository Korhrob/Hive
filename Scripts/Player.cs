using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{

    private const float half_sprite_height = 0.5f; // halfsize / size

    private float x_direction;
    private float y_direction;
    private float movespeed = 6f;
    private float jump_speed = -15f;
    private float vertical_speed = 0f;
    private int coyote_time = 0;
    private int harvest_inverval = 0;

    private int life;
    private int carry_capacity;
    private Inventory inventory;

    private Vector3 spawn_position;

    public float difference;

    private void Start()
    {
        life = Game.MaxLife;
        carry_capacity = Game.MaxCarryCapacity;
        spawn_position = transform.position;

        inventory = new Inventory();
    }

    private void Update()
    {
        x_direction = Input.GetAxisRaw("Horizontal");
        y_direction = Input.GetAxisRaw("Vertical");

        if (Input.GetKeyDown("space"))
        {
            Interact();
        }
    }

    private void FixedUpdate()
    {
        Movement();
        ApplyGravity();
        Pickup();

        if (harvest_inverval > 0)
            harvest_inverval--;
    }

    private void Movement()
    {

        RaycastHit2D[] rays;
        rays = Physics2D.RaycastAll(transform.position, Vector3.right * x_direction, 0.5f, Game.PlatformLayer);

        foreach (RaycastHit2D r in rays)
        {
            if (r.collider.CompareTag("Dropdown"))
                continue;
            x_direction = 0;
        }

        Vector2 pos = transform.position;
        pos.x += x_direction * movespeed * Time.fixedDeltaTime;
        transform.position = pos;

        //if (Physics2D.Raycast(transform.position, Vector2.right * x_direction, Game.PlatformLayer))
        //    transform.position = pos;

        if (y_direction > 0 && coyote_time > 0)
        {
            coyote_time = 0;
            vertical_speed = jump_speed;
        }
    }

    private void ApplyGravity()
    {
        float v = Mathf.Clamp(vertical_speed * Time.fixedDeltaTime, 0f, 0.5f);

        if (transform.position.y < -10f)
        {
            // health-- return to map if health > 0
            transform.position = spawn_position;
        }

        if (vertical_speed < Game.MaxGravity)
        {
            float modifier = Mathf.Clamp(-y_direction, 0f, 1f);
            vertical_speed += (Game.Gravity + modifier);
        }

        if (coyote_time > 0)
            coyote_time--;

        RaycastHit2D[] rays;
        rays = Physics2D.RaycastAll(transform.position, Vector3.down, 0.502f + v, Game.PlatformLayer);

        foreach (RaycastHit2D r in rays)
        {
            if (r.distance < 0.475f)
                continue;
            if (r.collider.CompareTag("Dropdown") && y_direction < 0)
                continue;
            if (vertical_speed > 0f)
            {
                vertical_speed = 0f;
                coyote_time = 8;
                if (r.distance < half_sprite_height)
                {
                    //Debug.Log($"position fix");
                    Vector3 fix = r.point;
                    fix.y += half_sprite_height;
                    transform.position = fix;
                }
            }
        }

        Vector2 pos = transform.position;

        pos.y -= vertical_speed * Time.fixedDeltaTime;
        transform.position = pos;
    }

    private Vector2 GroundPosition()
    {
        Vector2 pos;

        pos = transform.position;
        pos.y -= half_sprite_height;
        return (pos);
    }

    private void Interact()
    {
        if (harvest_inverval > 0)
            return;

        RaycastHit2D hit;
        hit = Physics2D.CircleCast(transform.position, 1f, Vector3.zero, 1f, Game.InteractLayer);

        if (hit)
        {

            if (hit.collider.CompareTag("Anvil"))
            {
                Debug.Log("Craft!");
                inventory.Empty();
                return;
            }

            if (hit.collider.CompareTag("Resource"))
            {
                Debug.Log("Harvest!");

                IDamage d = hit.collider.GetComponent<IDamage>();
                if (d != null)
                    d.TakeDamage();

                harvest_inverval = 16;
            }

        }
        else
        {
            Debug.Log("nothing to interact with!");
        }
    }

    private void Pickup()
    {
        if (inventory == null)
        {
            //Debug.Log("null inventory");
            return;
        }

        if (inventory.NumItems() >= carry_capacity)
        {
            // ui, holding too many items
            return;
        }

        RaycastHit2D hit;
        hit = Physics2D.CircleCast(transform.position, 1f, Vector3.zero, 1f, Game.ItemLayer);

        if (hit)
        {
            ItemDrop item = hit.collider.GetComponent<ItemDrop>();

            if (item.pickup_delay <= 0)
            {
                inventory.AddItem(item.type, item.quantity);
                Debug.Log("Pickup Item!");
                hit.collider.gameObject.SetActive(false);
            }
        }

    }
}
