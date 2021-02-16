package fr.eseo.poo.projet.artiste.modele.formes;

import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;

@RunWith(Parameterized.class)
public class LigneTestParametresContient {
	
		private Coordonnees coord1; 
		private Coordonnees coord2; 
		private Coordonnees coordContient; 
		private boolean contient;
		
		public LigneTestParametresContient(Coordonnees coord1, Coordonnees coord2, Coordonnees coordContient, boolean contient) {
			this.coord1 = coord1; 
			this.coord2 = coord1; 
			this.coordContient = coordContient; 
			this.contient = contient;
		}

		@Parameters(name= "dataLigne[{index}] : {0}, {1}, {2}, {3}") 
		public static Collection<Object[]>dataLigne(){
			Object[][] dataLigne = new Object[][] {
				{new Coordonnees(10, 10), new Coordonnees(20, 20), new Coordonnees(10, 10), true},
				{new Coordonnees(10, 10), new Coordonnees(5, 5), new Coordonnees(10.1, 10), false},
				{new Coordonnees(10, 10), new Coordonnees(5, 5), new Coordonnees(10, 10), true},
				{new Coordonnees(10, 10), new Coordonnees(20, 5), new Coordonnees(15, 7.5), false},
				{new Coordonnees(10, 10), new Coordonnees(5, 20), new Coordonnees(9.9, 10), false},
				{new Coordonnees(52.6, 28.5), new Coordonnees(10.5, 32.6), new Coordonnees(52.6, 28.5), true},
				{new Coordonnees(-52.6, 28.5), new Coordonnees(10.5, 32.6), new Coordonnees(10.6, 32.7), false},
				{new Coordonnees(1.1, 0.9), new Coordonnees(26.1, 0.2), new Coordonnees(1.1, 0.9), true}
			};
			
			return Arrays.asList(dataLigne);}
		
		
		@Test
		public void testContient() {
			LigneTestParametresContient testContient = new LigneTestParametresContient(coord1, coord2, coordContient, contient);
			Ligne ligne = new Ligne(testContient.coord1);
			ligne.setC2(testContient.coord2);
			assertEquals("Le point est bien contenu dans la ligne", contient, ligne.contient(coordContient));
		}

}
