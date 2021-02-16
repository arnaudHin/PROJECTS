package fr.eseo.poo.projet.artiste.modele;

import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;


@RunWith(Parameterized.class)
public class CoordonneesTestDistanceVersParameterized {
	private double abscisse1;
	private double ordonnee1;
	private double abscisse2;
	private double ordonnee2;
	private double distance;
	
	public CoordonneesTestDistanceVersParameterized(double abscisse1, double ordonnee1, double abscisse2,
			double ordonnee2, double distance) {
		this.abscisse1 = abscisse1;
		this.ordonnee1 = ordonnee1;
		this.abscisse2 = abscisse2;
		this.ordonnee2 = ordonnee2;
		this.distance = distance;
	}
	
		@Parameters(name= "dt[{index}] : {0}, {1}, {2}, {3}, {4} ") 
		public static Collection<Object[]>dt(){
			Object[][] data = new Object[][] {
				{0.0, 0.0, 1.0, 1.0, 1.414},
				{1.0, 1.0, 2.0, 2.0, 1.414},
				{2.0, 2.0, 1.0, 1.0, 1.414},
				{0.0, 0.0, -1.0, -1.0, 1.414},
				{0.0, 0.0, 0.0, 0.0, 0},
				{2.0, 0.0, 2.0, 2.0, 2},
				{2.0, -2.0, 2.0, 2.0, 4},
				{-2.0, -2.0, 2.0, 2.0, 5.65}
			};
			return Arrays.asList(data);
		}	
		@Test
		public void testVersDistance() {
			CoordonneesTestDistanceVersParameterized coords = new CoordonneesTestDistanceVersParameterized(
					abscisse1, ordonnee1, abscisse2, ordonnee2, distance);
			Coordonnees coord1 = new Coordonnees(coords.abscisse1, coords.ordonnee1);
			Coordonnees coord2 = new Coordonnees(coords.abscisse2, coords.ordonnee2);
			
			assertEquals("mauvaise distance", distance, coord1.distanceVers(coord2), 0.01);
		}	
}
