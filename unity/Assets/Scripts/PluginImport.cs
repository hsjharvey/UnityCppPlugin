using System;
using System.Runtime.InteropServices;
using TMPro.EditorUtilities;
using UnityEngine;

public class PluginImport : MonoBehaviour
{
    //Lets make our calls from the Plugin
    [DllImport("Dll4", CallingConvention = CallingConvention.Cdecl)]
    private static extern int PrintANumber();

    [DllImport("Dll4", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr PrintHello();

    [DllImport("Dll4", CallingConvention = CallingConvention.Cdecl)]
    private static extern int AddTwoIntegers(int i1, int i2);

    [DllImport("Dll4", CallingConvention = CallingConvention.Cdecl)]
    private static extern float AddTwoFloats(float f1, float f2);

    [DllImport("Dll4", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr test();

    [DllImport("Dll4", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr generate_distribution(IntPtr which_data, int length, int rd_seed);

    [DllImport("Dll4", CallingConvention = CallingConvention.Cdecl)]
    public static extern int ReleaseMemory(IntPtr ptr);

    void Start()
    {
        Debug.Log(PrintANumber());
        Debug.Log(Marshal.PtrToStringAnsi(PrintHello()));
        Debug.Log(AddTwoIntegers(2, 2));
        Debug.Log(AddTwoFloats(2.5F, 4F));


        /* the follow example applies for integer numbers*/
        IntPtr ptr = test();  //FYI: ptr refers to pointer
        int arrayLength = Marshal.ReadInt32(ptr);
        // points to arr[1], which is first value
        // IntPtr refers to Integer pointer, which is the physical address in the memory
        // where cpp stores the value
        IntPtr start = IntPtr.Add(ptr, 4);
        int[] result = new int[arrayLength];
        Marshal.Copy(start, result, 0, arrayLength);

        ReleaseMemory(ptr);

        /* the follow example applies for float numbers*/
        string which_data = "gaussian";
        IntPtr string_to_ptr = (IntPtr)Marshal.StringToHGlobalAnsi(which_data);
        IntPtr ptr_start = generate_distribution(string_to_ptr, 5000, 52123);
        Marshal.FreeHGlobal(string_to_ptr);
        int arrayLengthA = 5000;
        // points to arr[1], which is first value
        // in c++ int size=4 bytes, float size=4 bytes
        // add is used to move to the NEXT address of where the value is stored
        float[] resultA = new float[arrayLengthA];
        Marshal.Copy(ptr_start, resultA, 0, arrayLength);

        /* prints out first five values received from cpp */
        for (int i = 0; i < 5; i++)
        {
            Debug.Log(resultA[i]);
        }

        ReleaseMemory(ptr_start);
    }
}