using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class Leave : MonoBehaviour
{
    [SerializeField] TMP_Text trolled;
    [SerializeField] TMP_Text nvm1;
    [SerializeField] TMP_Text nvm2;
    private IEnumerator yeild;

    private void Awake()
    {
        infoText.gameObject.SetActive(false);
    }

    public void Gone()
    {
        trolled.gameObject.SetActive(true);
        StartCoroutine(troll());
    }

    private IEnumerator troll()
    {
        yield return new WaitForSeconds(15f);

        nvm1.gameObject.SetActive(true);
        nvm2.gameObject.SetActive(true);

        yield return new WaitForSeconds(0.5f);

        Application.Quit();
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
