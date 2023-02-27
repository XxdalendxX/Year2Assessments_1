using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CharacterController))]
public class PlayerMovement : MonoBehaviour
{
    CharacterController controller;
    GameObject player;

    [Header("Movement")]
    [SerializeField, Range(5, 25)] float speed = 10;
    [SerializeField] bool JumpInput;
    [SerializeField] Vector3 velocity;
    [SerializeField, Range(-15, -1)] float gravy = -9.8f;

    Vector2 moveInput = new Vector2();

    [Header("Variables")]
    [SerializeField, Range(5, 25)] float jumpVelocity = 5;

    [Header("Checks")]
    [SerializeField] bool isGrounded;

    [Header("Ground Check")]
    [SerializeField] Transform groundCheck;
    [SerializeField] float groundDistance = 0.4f;
    [SerializeField] LayerMask groundMask;

    // Start is called before the first frame update
    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
        controller = GetComponent<CharacterController>();
    }

    // Update is called once per frame
    void Update()
    {
        isGrounded = Physics.CheckSphere(groundCheck.position, groundDistance, groundMask);

        if (isGrounded && velocity.y < 0)
        {
            velocity.y = -2f;
        }




        moveInput.x = Input.GetAxis("Horizontal");
        moveInput.y = Input.GetAxis("Vertical");


        Vector3 move = transform.right * moveInput.x + transform.forward * moveInput.y;

        controller.Move(move * speed * Time.deltaTime);

        velocity.y += gravy * Time.deltaTime;

        controller.Move(velocity * Time.deltaTime);
    }
}
