using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class UI : MonoBehaviour
{

    public static UI instance;

    [SerializeField] private TMP_Text oreCount;
    [SerializeField] private TMP_Text logCount;

    private void Awake()
    {
        instance = this;
    }

    public void UpdateResourceCount(int[] inventory)
    {
        oreCount.text = $"{inventory[0]}";
        logCount.text = $"{inventory[1]}";
    }


}
