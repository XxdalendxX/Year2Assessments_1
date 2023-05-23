using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class TheUppinator : MonoBehaviour
{
    [SerializeField] Ragdoll ragdoll;

    [SerializeField, Range(0,1000)] float height;

    private void Awake()
    {
        infoText.gameObject.SetActive(false);
    }

    public void Uppsies()
    {
        ragdoll.RagdollOn = true;

        Transform body = ragdoll.gameObject.transform;

        Debug.Log("uppsies");

        StartCoroutine(Daisies(body));
        
    }

    [SerializeField, Range(0, 1000)] float push = 100;
    private IEnumerator Daisies(Transform body)
    {
        yield return new WaitForSeconds(3f);

        Vector3 vector = new Vector3(0, 100, 0);

        while (body.position.y < height)
        {
            body.Translate(vector * Time.deltaTime, Space.World);
            yield return new WaitForEndOfFrame();
        }

        StartCoroutine(Downsies(body));

        yield return null;
    }

    private IEnumerator Downsies(Transform body)
    {
        yield return new WaitForSeconds(10f);

        body.Translate(new Vector3(0, -(height), 0));

        ragdoll.RagdollOn = false;
       
        yield return null;
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
