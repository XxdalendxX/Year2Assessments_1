using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TheUppinator : MonoBehaviour
{
    [SerializeField] Ragdoll ragdoll;

    [SerializeField, Range(0,1000)] float height;
    
    public void Uppsies()
    {
        ragdoll.RagdollOn = true;

        Transform body = ragdoll.gameObject.transform;

        Debug.Log("uppsies");

        StartCoroutine(Daisies(body));
    }

    private IEnumerator Daisies(Transform body)
    {
        yield return new WaitForSeconds(3f);

        Vector3 vector = new Vector3(0, 100, 0);

        while (body.position.y < height)
        {
            body.Translate(vector * Time.deltaTime, Space.World);
            yield return new WaitForEndOfFrame();
        }

        yield return null;
    }
}
