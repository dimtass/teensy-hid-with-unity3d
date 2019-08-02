using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class QuitButton : MonoBehaviour
{
    private Button btn_quit;
    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("Quit button added...");
        btn_quit = GetComponent<Button>();
        btn_quit.onClick.AddListener(QuitGame);
    }

    // Update is called once per frame
    private void QuitGame()
    {
        Debug.Log("BQuiting...");
        Application.Quit();
    }
}
