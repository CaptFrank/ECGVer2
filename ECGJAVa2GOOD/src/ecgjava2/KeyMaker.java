/*
 * Copyright (C) 2011 Francis Papineau, Thai Nguyen
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

import java.io.File;
import java.security.NoSuchAlgorithmException;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.KeySpec;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;

/**
 * The KeyMaker class is used to create keys.
 * 
 * @author Francis Papineau
 * @author Thai Nguyen
 */
public class KeyMaker {
    /**
     * Creates a SecretKey using the given password and the PBE, MDS, and DES 
     * encryption algorithm.
     * 
     * @param password
     * @return 
     */
    public static SecretKey createKey(char[] password) {
        try {
            KeySpec keySpec = new PBEKeySpec(password);
            SecretKey key = SecretKeyFactory.getInstance(
                                    "PBEWithMDSandDES").generateSecret(keySpec);
            return key;
        } catch (InvalidKeySpecException ex) {
            Logger.getLogger(KeyMaker.class.getName()).log(Level.SEVERE, null, ex);
        } catch (NoSuchAlgorithmException ex) {
            Logger.getLogger(KeyMaker.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }
}
