using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Threading;
using UnityEngine;

public class HID_Controller : MonoBehaviour
{
    private static MemoryMappedFile mmf;
    private static byte[] hid_buf;
    enum DataIndex {
        PREAMBLE = 0, X = 2, Y = 6, Z = 10,
        qW = 14, qX = 18, qY = 22, qZ = 26
    };

    // Start is called before the first frame update
    void Start()
    {
        hid_buf = new byte[64];

        // transform.Rotate(30.53f, -5.86f, -6.98f);
        Debug.developerConsoleVisible = true;
        Debug.Log("Unity3D demo started...");

        mmf = MemoryMappedFile.CreateFromFile("/tmp/hid-shared-buffer", FileMode.OpenOrCreate, "/tmp/hid-shared-buffer");
        using (var stream = mmf.CreateViewStream()) {
            var data = stream.Read(hid_buf, 0, 64);
            if (data > 0) {
                Debug.Log("Data in: " + data);
                float hid_x = System.BitConverter.ToSingle(hid_buf, 2);
                Debug.Log("x: " + hid_x);
            }
        }


    }

    // Update is called once per frame
    void Update()
    {
        using (var stream = mmf.CreateViewStream()) {
            var data = stream.Read(hid_buf, 0, 64);
            if (data > 0) {
                float qw = System.BitConverter.ToSingle(hid_buf, (int) DataIndex.qW);
                float qx = System.BitConverter.ToSingle(hid_buf, (int) DataIndex.qX);
                float qy = System.BitConverter.ToSingle(hid_buf, (int) DataIndex.qY);
                float qz = System.BitConverter.ToSingle(hid_buf, (int) DataIndex.qZ);
                transform.rotation = new Quaternion(-qy, -qz, qx, qw);
            }
        }
    }
}
