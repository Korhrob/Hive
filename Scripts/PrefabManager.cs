using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PrefabManager : MonoBehaviour
{

    public static PrefabManager instance;

    public GameObject itemDropPrefab;

    private void Awake()
    {
        instance = this;
    }

    public void SpawnItemDrop(Vector2 position, Item.ID type, int quantity)
    {
        GameObject obj = Instantiate(itemDropPrefab, position, Quaternion.identity);
        ItemDrop item = obj.GetComponent<ItemDrop>();

        item.Initialize(type, quantity);
    }

}
