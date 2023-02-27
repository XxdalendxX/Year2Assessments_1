using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
public class CharacterMover : MonoBehaviour
{
    //Controller Variable
    CharacterController controller;

    [Header("Movement")]
    [SerializeField, Range(5, 25)] float speed = 10;
    [SerializeField] bool JumpInput;
    [SerializeField] Vector3 velocity;
    Vector2 moveInput = new Vector2();

    [Header("Variables")]
    [SerializeField, Range(5, 25)] float jumpVelocity = 5;

    [Header("Checks")]
    [SerializeField] bool isGrounded;

    
    
    

    void Update()
    {
        moveInput.x = Input.GetAxis("Horizontal");
        moveInput.y = Input.GetAxis("Vertical");
        JumpInput = Input.GetButton("Jump");
    }

    void Start()
    {
        controller= GetComponent<CharacterController>();
    }

    void FixedUpdate()
    {
        Vector3 delta;

        //Movement through WASD and the arrow keys
        delta = (moveInput.x * Vector3.right + moveInput.y * Vector3.forward) * speed * Time.fixedDeltaTime;
        if(isGrounded || moveInput.x != 0 || moveInput.y != 0)
        {
            velocity.x = delta.x;
            velocity.z = delta.z;
        }

        //Check for signs of a jumping attempt
        if(JumpInput && isGrounded)
        {
            velocity.y = jumpVelocity;
        }

        //Applies gravity
        velocity += Physics.gravity * Time.fixedDeltaTime;

        //Checks whether we've hit the ground as a result of falling and promptly removes velocity
        if(isGrounded && velocity.y < 0)
        {
            velocity.y = 0;
        }

        //Applies to the positional update of the character
        delta += velocity * Time.fixedDeltaTime;

        controller.Move(delta);
        isGrounded = controller.isGrounded;
    }
}
