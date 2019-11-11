using System;
using System.Collections.Generic;
using System.Numerics;
using System.Security.Cryptography;
using System.Text;

namespace HMAC
{
    public class Hmac
    {
        private byte[] exclusiveOR(byte[] arr1, byte[] arr2)
        {
            if (arr1.Length != arr2.Length)
                throw new ArgumentException("arr1 and arr2 are not the same length");

            byte[] result = new byte[arr1.Length];

            for (int i = 0; i < arr1.Length; ++i)
                result[i] = (byte)(arr1[i] ^ arr2[i]);

            return result;
        }

        private String arrayToHexString(byte[] arr)
        {
            var sb = new StringBuilder();
            for (int i = 0; i < arr.Length; ++i)
                sb.Append(arr[i].ToString("x2"));
            return sb.ToString();
        }
        public String randomGenerator()                            //create random number
        {
            RNGCryptoServiceProvider rng = new RNGCryptoServiceProvider();
            byte[] randomNumber = new byte[64];
            rng.GetBytes(randomNumber);
            return arrayToHexString(randomNumber);
        }

        private String GetMD5Hash(MD5 md5Hash, String input)
        {
            byte[] data = md5Hash.ComputeHash(Encoding.UTF8.GetBytes(input));
            return arrayToHexString(data);
        }

        public String Hmac_func(String key, String msg)
        {
            if (key.Length > 64)
            {
                using (MD5 md5Hash = MD5.Create())
                {
                    key = GetMD5Hash(md5Hash, key);
                }
            }
            if (key.Length < 64)
            {
                StringBuilder builder = new StringBuilder();
                for (int i = 0; i < 64 - key.ToString().Length; i++)
                {
                    builder.Append('0');
                }
                key += builder.ToString();
            }

            byte[] ipad = new byte[64];
            byte[] opad = new byte[64];
            for (int i = 0; i < ipad.Length; i++)
            {
                ipad[i] = 0x36;
                opad[i] = 0x5c;
            }
            byte[] ikeypad = exclusiveOR(ipad, Encoding.UTF8.GetBytes(key));
            byte[] okeypad = exclusiveOR(opad, Encoding.UTF8.GetBytes(key));

            String hash;
            using (MD5 md5Hash = MD5.Create())
            {
                hash = GetMD5Hash(md5Hash, arrayToHexString(okeypad) + GetMD5Hash(md5Hash, arrayToHexString(ikeypad) + msg));
            }
            return hash;
        }
    }
}
