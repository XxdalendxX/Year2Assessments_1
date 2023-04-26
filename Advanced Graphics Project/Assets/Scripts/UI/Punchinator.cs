using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Punchinator : MonoBehaviour
{
    [SerializeField] Animator animator;
    Ragdoll ragdoll;
    Transform tBody;
    Rigidbody rBody;
    [SerializeField] GameObject hand;

    private void Start()
    {
        ragdoll = animator.GetComponent<Ragdoll>();
        tBody = ragdoll.transform;
        rBody = hand.GetComponent<Rigidbody>();
    }

    public void Punching()
    {
        animator.Play("Punch");

        StartCoroutine(Daisies());
    }

    private IEnumerator Daisies()
    {
        yield return new WaitForSeconds(0.3f);

        ragdoll.RagdollOn = true;
        rBody.AddForce(-10000, 0, 0);

        StartCoroutine(Downsies(tBody));

        yield return null;
    }

    private IEnumerator Downsies(Transform body)
    {
        yield return new WaitForSeconds(4f);

        ragdoll.RagdollOn = false;
        tBody.Rotate(new Vector3(0,90,0 ), Space.World);
        tBody.Translate(0, 1, 0);
        animator.Play("Idle");

        yield return null;
    }

}
