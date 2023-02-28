using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CharacterController)), SelectionBase]
public class PlayerMovement : MonoBehaviour
{
    CharacterController controller;
    GameObject player;

    [Header("Movement")]

        //public
    [SerializeField, Range(1, 25)] float speed = 10;
    [SerializeField, Range(1, 25)] float jumpHeight = 5;
    [SerializeField, Range(1, 15)] float gravity = 9.8f;

        //private
    bool jumpInput;
    [SerializeField] Vector3 velocity;
    Vector2 moveInput = new Vector2();
    

    [Header("Checks")]

        //public
    [SerializeField] bool isGrounded;


    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
        controller = GetComponent<CharacterController>();
    }

    void Update()
    {
        moveInput.x = Input.GetAxis("Horizontal");
        moveInput.y = Input.GetAxis("Vertical");
        jumpInput = Input.GetButton("Jump");
    }

    void FixedUpdate()
    {
        isGrounded = controller.isGrounded; 

        Vector3 delta;

        //Movement through WASD and the arrow keys
        delta = (moveInput.x * Vector3.right + moveInput.y * Vector3.forward) * speed * Time.fixedDeltaTime;
        if (isGrounded || moveInput.x != 0 || moveInput.y != 0)
        {
            velocity.x = delta.x;
            velocity.z = delta.z;
        }

        //Check for signs of a jumping attempt
        if (jumpInput && isGrounded)
        {
            //velocity.y = jumpHeight;
            velocity.y = Jump();
        }

        //Checks whether we've hit the ground as a result of falling and promptly removes velocity
        if(isGrounded && velocity.y < 0)
        {
            velocity.y = 0;
        }

        //Applies gravity
        velocity.y -= gravity * Time.fixedDeltaTime;


        Vector3 move = transform.right * moveInput.x + transform.forward * moveInput.y;

        controller.Move(move * speed * Time.fixedDeltaTime);


        controller.Move(velocity * Time.fixedDeltaTime);
    }

    float Jump()
    {
        return Mathf.Sqrt(2 * gravity * jumpHeight);
    }
}

/*
 * ADDITIONAL CODE:
 * Physics.CheckSphere(groundCheck.position, groundDistance, groundMask);
 * [Header("Ground Check")]
 * [SerializeField] Transform groundCheck;
 * [SerializeField] float groundDistance = 0.4f;
 * [SerializeField] LayerMask groundMask;
 */