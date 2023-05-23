using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Resetinator : MonoBehaviour
{

    private void Awake()
    {
        infoText.gameObject.SetActive(false);
    }

    public void Resetting()
    {
        SceneManager.LoadScene(0);

        Button button;
    }

    [SerializeField] TMP_Text infoText;
    public void InfoTextToggle()
    {
        if (infoText.gameObject.activeSelf == false)
            infoText.gameObject.SetActive(true);
        else
            infoText.gameObject.SetActive(false);
    }

}
