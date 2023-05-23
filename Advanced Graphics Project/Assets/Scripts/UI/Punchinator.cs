using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class Punchinator : MonoBehaviour
{
    [SerializeField] Animator animator;
    Ragdoll ragdoll;
    Transform tBody;
    Rigidbody rBody;
    [SerializeField] GameObject hand;

    [Header("Punchinator")]
    [SerializeField] float pushX = 0;
    [SerializeField] float pushY = 0;
    [SerializeField] float pushZ = 0;
    [SerializeField] float animationTime = 0.45f;

    private void Awake()
    {
        infoText.gameObject.SetActive(false);
    }

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
        yield return new WaitForSeconds(animationTime);

        ragdoll.RagdollOn = true;

        rBody.AddForce(pushX, pushY, pushZ);
        yield return new WaitForSeconds(0.1f);
        StartCoroutine(Downsies(tBody));

        yield return null;
    }

    private IEnumerator Downsies(Transform body)
    {
        yield return new WaitForSeconds(2.1f);

        ragdoll.RagdollOn = false;
        tBody.SetPositionAndRotation(new Vector3(0,0.1f,0), new Quaternion(0, 180, 0, 1));
        tBody.Rotate(new Vector3(0, -90, 0), Space.World);
        animator.Play("Idle");

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
