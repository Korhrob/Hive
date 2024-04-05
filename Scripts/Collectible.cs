using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Collectible : MonoBehaviour, IDamage
{

    int max_quantity = 3;
    int quantity;
    public Item.ID type;

    private void Start()
    {
        quantity = max_quantity;
    }

    public void TakeDamage()
    {
        if (quantity <= 0)
            return;

        // spawn particles

        Vector3 offset;
        offset = new Vector3(Random.Range(-0.5f, 0.5f), Random.Range(0.25f, 0.25f), -0.25f);

        PrefabManager.instance.SpawnItemDrop(transform.position + offset, type, 1);

        quantity--;

        if (quantity == 0)
        {
            // spawn big particles
            gameObject.SetActive(false);
        }

    }

}
