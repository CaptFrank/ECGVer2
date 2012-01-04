/*
 * Copyright (C) 2012 Thai Nguyen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
package ecgjava2;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.CipherOutputStream;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;

/**
 * The Encrypter class encrypts and decrypts things.
 * 
 * @author Thai Nguyen
 */
public class Encrypter {
    private Cipher eCipher;
    private Cipher dCipher;
    
    /**
     * Constructs an instance of the Encrypter class with a given SecretKey key 
     * and with the DES encryption algorithm.
     * 
     * @param key - A SecretKey used to encryption and decryption.
     */
    public Encrypter(SecretKey key) {
        try {
            eCipher = Cipher.getInstance("DES");
            dCipher = Cipher.getInstance("DES");
            eCipher.init(Cipher.ENCRYPT_MODE, key);
            eCipher.init(Cipher.DECRYPT_MODE, key);
        } catch (NoSuchAlgorithmException ex) {
            Logger.getLogger(Encrypter.class.getName()).log(Level.SEVERE, null, ex);
        } catch (NoSuchPaddingException ex) {
            Logger.getLogger(Encrypter.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InvalidKeyException ex) {
            Logger.getLogger(Encrypter.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * Encrypts String str using the algorithm that was defined.
     * 
     * @param str - The string to be encrypted
     * @return An encrypted string of str if encrypting was successful.
     * @return An empty string otherwise.
     */
    public String encrypt(String str) {
        try {
            byte[] utf8 = str.getBytes("UTF8");
            byte[] enc = eCipher.doFinal(utf8);
//            /* Fill unencrypted array with useless values. This prevents 
//             * people with access to the memory to get anything (maybe?)
//             */
//            Arrays.fill(utf8, (byte) 0x0); 
            return new sun.misc.BASE64Encoder().encode(enc);
        } catch (UnsupportedEncodingException ex) {
            Logger.getLogger(Encrypter.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IllegalBlockSizeException ex) {
            Logger.getLogger(Encrypter.class.getName()).log(Level.SEVERE, null, ex);
        } catch (BadPaddingException ex) {
            Logger.getLogger(Encrypter.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }
    public java.io.File encrypt(java.io.File file) {
        
        return file;
    }
    
    public String decrypt(String str) {
        try {
            byte[] dec = new sun.misc.BASE64Decoder().decodeBuffer(str);
            byte[] utf8 = dCipher.doFinal(dec);
            return new String(utf8, "UTF8");
        } catch (IllegalBlockSizeException ex) {
            Logger.getLogger(Encrypter.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(Encrypter.class.getName()).log(Level.SEVERE, null, ex);
        } catch (BadPaddingException ex) {
            Logger.getLogger(Encrypter.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }
    public java.io.File decrypt(java.io.File file) {
        return file;
    }
}
