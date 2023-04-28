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
        yield return new WaitForSeconds(0.35f);

        ragdoll.RagdollOn = true;
        rBody.AddForce(-10000, 10000, 0);

        StartCoroutine(Downsies(tBody));

        yield return null;
    }

    private IEnumerator Downsies(Transform body)
    {
        yield return new WaitForSeconds(2f);

        ragdoll.RagdollOn = false;
        tBody.SetPositionAndRotation(new Vector3(0,0,0), new Quaternion(0, 180, 0, 1));
        tBody.Rotate(new Vector3(0, -90, 0), Space.World);
        animator.Play("Idle");

        yield return null;
    }

}
