package fr.eseo.poo.projet.artiste.modele;

import static org.junit.Assert.assertEquals;
import java.util.Arrays;
import java.util.Collection;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

@RunWith(Parameterized.class)
public class CoordonneesTestAngleVersParameterized {
	
	private double abscisse1;
	private double ordonnee1;
	private double abscisse2;
	private double ordonnee2;
	private double angle;
	
	public CoordonneesTestAngleVersParameterized(double abscisse1, double ordonnee1, double abscisse2, 
			double ordonnee2, double angle) {
		this.abscisse1 = abscisse1;
		this.ordonnee1 = ordonnee1;
		this.abscisse2 = abscisse2;
		this.ordonnee2 = ordonnee2;
		this.angle = angle;
	}
	
		@Parameters(name= "dt[{index}] : {0}, {1}, {2}, {3}, {4} ")

		public static Collection<Object[]>dt(){
			Object[][] data = new Object[][] {
				{0.0, 0.0, 0.0, 0.0, 0},
				{0.0, 0.0, 2.0, 0.0, 0},
				{0.0, 0.0, 1.0, 1.0, Math.PI/4},
				{0.0, 0.0, 0.0, 1.0, Math.PI/2},
				{0.0, 0.0, -1.0, 0.0, Math.PI},
				{0.0, 0.0, -1.0, 1.0, Math.PI/2 + Math.PI/4},
				{-2.0, -2.0, 2.0, 2.0, Math.PI/4},
				{0.0, 0.0, -1.0, -1.0, -Math.PI/2 - Math.PI/4},
				{0.0, 0.0, 1.0, -1.0, -Math.PI/4},
				{0.0, 0.0, 0.0, -1.0, -Math.PI/2}
			};
			return Arrays.asList(data);}
		
		@Test
		public void testVersAngle() {
			CoordonneesTestAngleVersParameterized coords = new CoordonneesTestAngleVersParameterized(abscisse1,
					ordonnee1, abscisse2, ordonnee2, angle);
			Coordonnees coord1 = new Coordonnees(coords.abscisse1, coords.ordonnee1);
			Coordonnees coord2 = new Coordonnees(coords.abscisse2, coords.ordonnee2);
			
			assertEquals("mauvaise distance", angle, coord1.angleVers(coord2), 0.01);
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
}
