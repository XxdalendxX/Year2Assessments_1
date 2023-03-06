using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Platform : MonoBehaviour
{
    [SerializeField]
    Transform startPos, endPos;
    [SerializeField] float speed = 3f;
    [SerializeField] bool _switch = false;

    Rigidbody rb;
    CharacterController cc;

    [SerializeField] Vector3 velocity;

    private void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    private void FixedUpdate()
    {
        
        
        Vector3 initialPosition = transform.position;
        Vector3 finalPosition;
        if (!_switch)
        {
            transform.position = Vector3.MoveTowards(transform.position, endPos.position, speed * Time.fixedDeltaTime);
            finalPosition = transform.position;
            velocity = GetVelocity(initialPosition, finalPosition);
        }
        else if (_switch)
        {
            transform.position = Vector3.MoveTowards(transform.position, startPos.position, speed * Time.fixedDeltaTime);
            finalPosition = transform.position;
            velocity = GetVelocity(initialPosition, finalPosition);
        }

            if (transform.position == endPos.position)
                _switch = true;
            else if (transform.position == startPos.position)
                _switch = false;

    }

    private void OnTriggerEnter(Collider other)
    {
       if (other.CompareTag("Player"))
       {
            cc = other.GetComponent<CharacterController>();
            other.transform.parent = this.transform;
       }
    }
    void OnTriggerStay(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            cc.Move(rb.velocity * Time.deltaTime);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            other.transform.parent = null;
            cc = null;
        }
    }

    private Vector3 GetVelocity(Vector3 initialPosition, Vector3 finalPosition)
    {
        return (finalPosition - initialPosition) / Time.fixedDeltaTime;
    }
}
